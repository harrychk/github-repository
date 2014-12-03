/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ofdm_outer_headerparser_bb_impl.h"

#define msg_port_id     pmt::mp("header_data")

namespace gr {
  namespace howto {

    ofdm_outer_headerparser_bb::sptr
    ofdm_outer_headerparser_bb::make(int fft_len, const std::vector<std::vector<int> > &occupied_carriers)
    {
      return gnuradio::get_initial_sptr
        (new ofdm_outer_headerparser_bb_impl(fft_len, occupied_carriers));
    }

    /*
     * The private constructor
     */
    ofdm_outer_headerparser_bb_impl::ofdm_outer_headerparser_bb_impl(int fft_len, const std::vector<std::vector<int> > &occupied_carriers)
      : sync_block("ofdm_outer_headerparser_bb",
              io_signature::make(1, 1, sizeof (gr_complex)),
              io_signature::make(0,0,0)),
	d_occupied_carriers(occupied_carriers),
	d_fft_len(fft_len)
    {
    	d_constellation = gr::howto::constellation_bpsk::make();
		for (unsigned i = 0; i < d_occupied_carriers.size(); i++) {
			for (unsigned j = 0; j < d_occupied_carriers[i].size(); j++) {
			  if (occupied_carriers[i][j] < 0) {
				d_occupied_carriers[i][j] += d_fft_len;
			  }
			  if (d_occupied_carriers[i][j] > d_fft_len || d_occupied_carriers[i][j] < 0) {
				throw std::invalid_argument("data carrier index out of bounds");
			  }

			  d_occupied_carriers[i][j] = (d_occupied_carriers[i][j] + fft_len/2) % fft_len;

			}
		}

		message_port_register_out(msg_port_id);
		set_output_multiple(6*d_occupied_carriers[0].size());
    }

    /*
     * Our virtual destructor.
     */
    ofdm_outer_headerparser_bb_impl::~ofdm_outer_headerparser_bb_impl()
    {
    }

    int
    ofdm_outer_headerparser_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];

        if (noutput_items < d_occupied_carriers[0].size()) {
		return 0;
		}

		std::vector<tag_t> tags;
		get_tags_in_range(
		  tags, 0,
		  nitems_read(0),
		  nitems_read(0)+d_occupied_carriers[0].size()*6   // 6 outer header symbols
		);

		int outer_header_len = 6;
		int carriers_size=d_occupied_carriers[0].size();
		std::vector<char> pid_bit(outer_header_len);
		std::vector<char> pid_buffer;
		std::vector<std::vector<int> > occupied_carriers_buffer;
		for(int i=0;i<carriers_size;i++){
			for(int j=0;j<outer_header_len;j++){
				pid_bit[j] = d_constellation->decision_maker(&in[j*carriers_size + i]);
			}

			char pid=0;
			for (int t = 0; t < outer_header_len ; t ++) {
				pid |= (pid_bit[t] & 0x01) << t;
			}

			if(check_pid(pid)){	// check if pid valid
				int index = check_pid_index(pid,pid_buffer);
				if( index != -1){
					occupied_carriers_buffer[index].push_back(d_occupied_carriers[0][i]);
				}else{
					pid_buffer.push_back(pid);
					std::vector<int> temp(1,d_occupied_carriers[0][i]);
					occupied_carriers_buffer.push_back(temp);

				}
			}

		}

		if(pid_buffer.size()){
			std::vector<int> occupied_carriers_total;
			for(int i=0;i<occupied_carriers_buffer.size();i++){
				for(int j=0;j<occupied_carriers_buffer[i].size();j++){
					occupied_carriers_total.push_back(occupied_carriers_buffer[i][j]);
				}
				occupied_carriers_total.push_back(-1);
			}

			tag_t tag;
			tag.key = pmt::string_to_symbol("occupied_carriers_total");
			tag.value = pmt::init_s32vector(occupied_carriers_total.size(),occupied_carriers_total);
			tags.push_back(tag);

			pmt::pmt_t dict(pmt::make_dict());
			for (unsigned i = 0; i < tags.size(); i++) {
				dict = pmt::dict_add(dict, tags[i].key, tags[i].value);
			}
			message_port_pub(msg_port_id, dict);

			// Tell runtime system how many output items we produced.
			return outer_header_len*carriers_size;
		}

		return 0;
	}

	int
	ofdm_outer_headerparser_bb_impl::check_pid_index(int pid, std::vector<char> &pid_buffer){
		for(int i=0;i<pid_buffer.size();i++){
			if(pid == pid_buffer[i])
				return i;
		}
		return -1;
	}

	bool
	ofdm_outer_headerparser_bb_impl::check_pid(char pid){
		char pid_ref[]= {7,11,13,14,19,21,22,25,26,28,15,60,58,57,3,5,6,9,10,12,17,18,20,24,33,34,36,40,48,62,61,59,55};
		int pid_ref_length=sizeof(pid_ref);
		for(int i=0;i<pid_ref_length;i++){
			if(pid==pid_ref[i])
				return true;
		}
		return false;
	}

  } /* namespace howto */
} /* namespace gr */

