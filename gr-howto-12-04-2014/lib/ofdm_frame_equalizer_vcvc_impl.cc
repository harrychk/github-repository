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

#include <gnuradio/expj.h>
#include <gnuradio/io_signature.h>
#include "ofdm_frame_equalizer_vcvc_impl.h"

#define M_TWOPI (2*M_PI)

namespace gr {
  namespace howto {

    ofdm_frame_equalizer_vcvc::sptr
    ofdm_frame_equalizer_vcvc::make(
	int fft_len,
	unsigned device_id,
	//const gr::howto::constellation_sptr &constellation,
	const std::vector<std::vector<int> > &pilot_carriers,
	const std::vector<std::vector<gr_complex> > &pilot_symbols,
	int cp_len,
	const std::string &len_tag_key,
	bool propagate_channel_state,
	int fixed_frame_len
    )
    {
      return gnuradio::get_initial_sptr (
	  new ofdm_frame_equalizer_vcvc_impl(
	    fft_len,  device_id, pilot_carriers, pilot_symbols, cp_len, len_tag_key, propagate_channel_state, fixed_frame_len
	  )
      );
    }

    ofdm_frame_equalizer_vcvc_impl::ofdm_frame_equalizer_vcvc_impl(
	int fft_len,
	unsigned device_id,
	//const gr::howto::constellation_sptr &constellation,
	const std::vector<std::vector<int> > &pilot_carriers,
	const std::vector<std::vector<gr_complex> > &pilot_symbols,
	//gr::howto::ofdm_equalizer_base::sptr equalizer,
	int cp_len,
	const std::string &len_tag_key,
	bool propagate_channel_state,
	int fixed_frame_len
    ) : tagged_stream_block("ofdm_frame_equalizer_vcvc",
	  io_signature::make(1, 1, sizeof (gr_complex) * fft_len),
	  io_signature::make(1, 1, sizeof (gr_complex) * fft_len),
	  len_tag_key),
      d_fft_len(fft_len),//equalizer->fft_len() to fft_len
	  d_device_id(device_id),
      //d_constellation(constellation),
      //d_occupied_carriers(0),
      d_pilot_carriers(pilot_carriers),
      d_pilot_symbols(pilot_symbols),
      d_cp_len(cp_len),
      //d_eq(equalizer),
      d_propagate_channel_state(propagate_channel_state),
      d_fixed_frame_len(fixed_frame_len),
      d_channel_state(fft_len, gr_complex(1, 0))
    {
      if (len_tag_key.empty() && fixed_frame_len == 0) {
	throw std::invalid_argument("Either specify a length tag or a frame length!");
      }
      if (d_fixed_frame_len < 0) {
	throw std::invalid_argument("Invalid frame length!");
      }
      if (d_fixed_frame_len) {
	set_output_multiple(d_fixed_frame_len);
      }
      set_relative_rate(1.0);

    }

    ofdm_frame_equalizer_vcvc_impl::~ofdm_frame_equalizer_vcvc_impl()
    {
    }

    void
    ofdm_frame_equalizer_vcvc_impl::parse_length_tags(
	const std::vector<std::vector<tag_t> > &tags,
	gr_vector_int &n_input_items_reqd
    ){
      if (d_fixed_frame_len) {
	n_input_items_reqd[0] = d_fixed_frame_len;
      } else {
	for (unsigned k = 0; k < tags[0].size(); k++) {
	  if (tags[0][k].key == pmt::string_to_symbol(d_length_tag_key_str)) {
	    n_input_items_reqd[0] = pmt::to_long(tags[0][k].value);
	    remove_item_tag(0, tags[0][k]);
	  }
	}
      }
    }


    int
    ofdm_frame_equalizer_vcvc_impl::work(int noutput_items,
	  gr_vector_int &ninput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int carrier_offset = 0;
      int frame_len = 0;
      if (d_fixed_frame_len) {
	frame_len = d_fixed_frame_len;
      } else {
	frame_len = ninput_items[0];
      }

      std::vector<tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+1);
      for (unsigned i = 0; i < tags.size(); i++) {
	if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_chan_taps") {
	  d_channel_state = pmt::c32vector_elements(tags[i].value);
	  remove_item_tag(0, tags[i]);
	}
	if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_carr_offset") {
	  carrier_offset = pmt::to_long(tags[i].value);
	}
	if (tags[i].key == pmt::string_to_symbol("occupied_carriers_total")) {
	  d_occupied_carriers_total = pmt::s32vector_elements(tags[i].value); // get total occupied carriers divided with -1
	  remove_item_tag(0, tags[i]);
	}
      }



      // Copy the frame and the channel state vector such that the symbols are shifted to the correct position
      if (carrier_offset < 0) {
	memset((void *) out, 0x00, sizeof(gr_complex) * (-carrier_offset));
	memcpy(
	    (void *) &out[-carrier_offset], (void *) in,
	    sizeof(gr_complex) * (d_fft_len * frame_len + carrier_offset)
	);
      } else {
	memset((void *) (out + d_fft_len * frame_len - carrier_offset), 0x00, sizeof(gr_complex) * carrier_offset);
	memcpy(
	    (void *) out, (void *) (in+carrier_offset),
	    sizeof(gr_complex) * (d_fft_len * frame_len - carrier_offset)
	);
      }



      // Correct the frequency shift on the symbols
      gr_complex phase_correction;
      for (int i = 0; i < frame_len; i++) {
	phase_correction = gr_expj(-M_TWOPI * carrier_offset * d_cp_len / d_fft_len * (i+1));
	for (int k = 0; k < d_fft_len; k++) {
	  out[i*d_fft_len+k] *= phase_correction;
	}
      }

      // initialize constellation
      gr::howto::constellation_sptr constellation_header = gr::howto::constellation_bpsk::make()->base();
      gr::howto::constellation_sptr constellation_data = gr::howto::constellation_qpsk::make()->base();


      //divide occupied carriers

		std::vector<std::vector<int> > occupied_carriers_buffer;
		get_occupied_carriers_buffer(occupied_carriers_buffer, d_occupied_carriers_total);

		for(int i=0;i<occupied_carriers_buffer.size();i++){
			int n_header_symbol = ceil((float)48/occupied_carriers_buffer[i].size());
			if(n_header_symbol < frame_len){
				int n_data_forecast = (frame_len*occupied_carriers_buffer[i].size()-48)/4; // may not fully occupy ofdm block
				int n_data_real = n_data_forecast*4;
				int n_data_symbol = frame_len-n_header_symbol + (48%occupied_carriers_buffer[i].size()>0 ? 1 : 0);
				std::vector<unsigned char> header_symbol(48,0);
				std::vector<gr_complex> data_symbol(n_data_real,gr_complex(0,0));

				std::vector<std::vector<int> > occ(1,occupied_carriers_buffer[i]);

				gr_complex * header = (gr_complex *) calloc(n_header_symbol*d_fft_len,sizeof(gr_complex));
				memcpy(header, out, n_header_symbol*d_fft_len*sizeof(gr_complex));
				gr::howto::ofdm_equalizer_simpledfe::sptr equalizer_header = gr::howto::ofdm_equalizer_simpledfe::make(
						  d_fft_len, constellation_header, occ, d_pilot_carriers, d_pilot_symbols);

				d_eq = equalizer_header->base();
				d_eq->reset();
				d_eq->equalize(header, n_header_symbol,48,0, d_channel_state); //start position is 0
				d_eq->get_channel_state(d_channel_state);


				//get header seq
				int n=0;
				for(int j=0;j<n_header_symbol;j++){
					for(int t=occupied_carriers_buffer[i].size()-1;t>=0;t--){  //because the buffer is reversed
						if(n<48){
							header_symbol[n]= constellation_header->decision_maker(&header[d_fft_len*j+occupied_carriers_buffer[i][t]]);
							n++;
						}
					}
				}

				free(header);
				// resolve header
				if(header_parser(header_symbol, tags)==d_device_id){
					int packet_len=0;
					for (unsigned a = 0; a < tags.size(); a++) {
						if (pmt::symbol_to_string(tags[a].key) == "packet_len") {
						  packet_len = pmt::to_long(tags[a].value);
						  packet_len = packet_len * 8 / 2;
						  tags[a].value = pmt::from_long(packet_len);
						}
					}


					//get data
					int symbol_offset = 48/ occupied_carriers_buffer[i].size();
					//gr_complex * data = (gr_complex *) calloc(n_data_symbol*d_fft_len,sizeof(gr_complex));
					//memcpy(data, out+symbol_offset, n_data_symbol*d_fft_len*sizeof(gr_complex));
					int start_pos= 48 ;  // # of symbols occupied by header in ofdm symbol

					gr::howto::ofdm_equalizer_simpledfe::sptr equalizer_data = gr::howto::ofdm_equalizer_simpledfe::make(
							  d_fft_len, constellation_data, occ, d_pilot_carriers, d_pilot_symbols);

					d_eq = equalizer_data->base();
					d_eq->reset();
					d_eq->equalize(out, frame_len,n_data_real,start_pos, d_channel_state);
					d_eq->get_channel_state(d_channel_state);


					//get data seq
					/*int n=0;
					for(int j=0;j<n_data_symbol;j++){
						for(int t=occupied_carriers_buffer[i].size()-1;t>=0;t--){  //because the buffer is reversed
							if(start_pos==0){
								if(n<n_data_real){
									//data_symbol[n]= constellation_data->decision_maker(&data[d_fft_len*j+occupied_carriers_buffer[i][t]]);
									data_symbol[n]= data[d_fft_len*j+occupied_carriers_buffer[i][t]];
									n++;
								}
							}else{
								start_pos--;
							}
						}
					}*/

					//free(data);


					/*memset((void *) out , 0x00, sizeof(gr_complex) *n_data_real);
					for(int m=0;m<n_data_real;m++){
						out[m]=data_symbol[m];
					}*/

					for (unsigned m = 0; m < tags.size(); m++) {
						if (pmt::equal(tags[m].key, pmt::string_to_symbol("device_id"))) {
							add_item_tag(0, nitems_written(0), tags[m].key, tags[m].value);
						}
						if (pmt::equal(tags[m].key, pmt::string_to_symbol("message_type"))) {
							add_item_tag(0, nitems_written(0), tags[m].key, tags[m].value);
						}
						if (pmt::equal(tags[m].key, pmt::string_to_symbol("packet_len"))) {
							add_item_tag(0, nitems_written(0), tags[m].key, tags[m].value);
						}
						if (pmt::equal(tags[m].key, pmt::string_to_symbol("packet_num"))) {
							add_item_tag(0, nitems_written(0), tags[m].key, tags[m].value);
						}
					}
					add_item_tag(0, nitems_written(0), pmt::string_to_symbol("start_position"), pmt::from_long(start_pos));
					add_item_tag(0, nitems_written(0), pmt::string_to_symbol("occupied_carriers"),
							pmt::init_s32vector(occupied_carriers_buffer[i].size(),occupied_carriers_buffer[i]));

					// add tags
					/*for (unsigned i = 0; i < tags.size(); i++) {
						if (pmt::symbol_to_string(tags[i].key) == "frame_len") {
						  tags[i].value=pmt::from_long(n_data_real);
						}

					}
					for (unsigned t = 0; t < tags.size(); t++) {
					  add_item_tag(0, nitems_written(0),
						tags[t].key,
						tags[t].value
					  );
					}*/


					//set_relative_rate(n_data_real);
					// Update the channel state regarding the frequency offset
					  phase_correction = gr_expj(M_TWOPI * carrier_offset * d_cp_len / d_fft_len * frame_len);
					  for (int k = 0; k < d_fft_len; k++) {
					d_channel_state[k] *= phase_correction;
					  }

					  // Housekeeping
					  if (d_propagate_channel_state) {
					add_item_tag(0, nitems_written(0),
						pmt::string_to_symbol("ofdm_sync_chan_taps"),
						pmt::init_c32vector(d_fft_len, d_channel_state));
					  }

					  if (d_fixed_frame_len && d_length_tag_key_str.empty()) {
					consume_each(frame_len);
					  }

					  return frame_len;
				}else{

				}

			}


		}




      // Do the equalizing

      /*gr::howto::ofdm_equalizer_simpledfe::sptr equalizer = gr::howto::ofdm_equalizer_simpledfe::make(
    		  d_fft_len, d_constellation, d_occupied_carriers, d_pilot_carriers, d_pilot_symbols);
      d_eq = equalizer->base();
      d_eq->reset();
      d_eq->equalize(out, frame_len, d_channel_state);
      d_eq->get_channel_state(d_channel_state);*/
		return 0;

    }

    void
	ofdm_frame_equalizer_vcvc_impl::get_occupied_carriers_buffer(std::vector<std::vector<int> > &buffer, std::vector<int> &total){
    	if(total.size()!=0){
    		for(int i=total.size()-1;i>=0;i--){
				if(total[i]==-1){
					std::vector<int> temp;
					buffer.push_back(temp);
				}else{
					buffer[buffer.size()-1].push_back(total[i]);
				}
			}
    	}

    }

    int
	ofdm_frame_equalizer_vcvc_impl::header_parser(std::vector<unsigned char> &in,std::vector<tag_t> &tags)
	{
    	//clean
    	for (unsigned i = 0; i < tags.size(); i++) {
			if (pmt::symbol_to_string(tags[i].key) == "device_id") {
			    tags.erase(tags.begin()+i); i--;
			}
			if (pmt::symbol_to_string(tags[i].key) == "message_type") {
				tags.erase(tags.begin()+i); i--;
			}
			if (pmt::symbol_to_string(tags[i].key) == "packet_num") {
				tags.erase(tags.begin()+i); i--;
			}
			if (pmt::symbol_to_string(tags[i].key) == "packet_len") {
				tags.erase(tags.begin()+i); i--;
			}
		}

	  unsigned header_len = 0;
	  unsigned header_num = 0;
	  unsigned device_id = 0;
	  unsigned message_type = 0;
	  tag_t tag;
	  unsigned char d_mask = 0x01;

	  int k = 0; // Position in "in"
	  for (int i = 0; i < 16 && k < 48; i += 1, k++) {
		  device_id |= (((int) in[k]) & d_mask) << i;
	  }
	  tag.key = pmt::string_to_symbol("device_id");
	  tag.value = pmt::from_long(device_id);
	  tags.push_back(tag);


	  for (int i = 0; i < 2 && k < 48; i += 1, k++) {
		  message_type |= (((int) in[k]) & d_mask) << i;
	  }
	  tag.key = pmt::string_to_symbol("message_type");
	  tag.value = pmt::from_long(message_type);
	  tags.push_back(tag);


	  for (int i = 0; i < 11 && k < 48; i += 1, k++) {
		  header_len |= (((int) in[k]) & d_mask) << i;
	  }

	  tag.key = pmt::string_to_symbol("packet_len");
	  tag.value = pmt::from_long(header_len);
	  tags.push_back(tag);

	  //if (d_num_tag_key == pmt::PMT_NIL) {
		//  k += 11;
	  //} else {
	for (int i = 0; i < 11 && k < 48; i += 1, k++) {
	  header_num |= (((int) in[k]) & d_mask) << i;
	}
	tag.key = pmt::string_to_symbol("packet_num");
	tag.value = pmt::from_long(header_num);
	tags.push_back(tag);
	  //}


	  d_crc_impl.reset();
	  d_crc_impl.process_bytes((void const *) &device_id, 2); // chk
	  d_crc_impl.process_bytes((void const *) &header_len, 2);
	  d_crc_impl.process_bytes((void const *) &header_num, 2);
	  unsigned char crc_calcd = d_crc_impl();
	  for (int i = 0; i < 8 && k < 48; i += 1, k++) {
	  if ( (((int) in[k]) & d_mask) != (((int) crc_calcd >> i) & d_mask) ) {
		return 0;
	  }
	  }

	  return device_id;
	}

  } /* namespace howto */
} /* namespace gr */

