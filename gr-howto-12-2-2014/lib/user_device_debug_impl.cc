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
#include "user_device_debug_impl.h"
#define msg_port_id     pmt::mp("ack")
namespace gr {
  namespace howto {

    user_device_debug::sptr
    user_device_debug::make(
    		const std::vector<unsigned char> &data,
    		const unsigned int device_id,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb)
    {
      return gnuradio::get_initial_sptr
        (new user_device_debug_impl(data, device_id, packet_len, request_utb, acknowledgement_btu, acknowledgement_utb,
        		acknowledgement_end_btu, acknowledgement_end_utb));
    }

    /*
     * The private constructor
     */
    user_device_debug_impl::user_device_debug_impl(
    		const std::vector<unsigned char> &data,
    		const unsigned int device_id,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb)
      : sync_block("user_device_debug",
              io_signature::make(0, 0, 0),
              io_signature::make(1, 1, sizeof(char))),
			  //io_signature::make(0, 0, 0)),
			  d_data(data),
		    d_device_id(device_id),
			d_packet_len(packet_len),
			d_request_utb(request_utb),
			d_acknowledgement_btu(acknowledgement_btu),
			d_acknowledgement_utb(acknowledgement_utb),
			d_acknowledgement_end_btu(acknowledgement_end_btu),
			d_acknowledgement_end_utb(acknowledgement_end_utb),
			d_next_tag_pos(0),
			d_offset(0)
    {
    	message_port_register_out(msg_port_id);
    }

    /*
     * Our virtual destructor.
     */
    user_device_debug_impl::~user_device_debug_impl()
    {
    }

    int
    user_device_debug_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
    	unsigned char *optr = (unsigned char *) output_items[0];


    	d_data=d_acknowledgement_end_utb;
    	int message_type=2;
        // Do <+signal processing+>
    	/*if(d_offset>noutput_items)
    		return -1;
    	unsigned int size = d_data.size ();
		unsigned int offset = d_offset;
		if(size == 0)
		  return -1;


		  for(int i = 0; i < noutput_items/2; i++) {
			optr[i] = d_data[offset++];
			if(offset >= size) {
			  offset = 0;
			}
		  }
		  if((noutput_items/2)%d_packet_len){
			  for(int j=0;j<d_packet_len-(noutput_items/2)%d_packet_len;j++){
				  optr[noutput_items/2+j] = 0;
			  }
		  }



		  noutput_items=noutput_items/2+d_packet_len-(noutput_items/2)%d_packet_len;
		  while(d_next_tag_pos < nitems_written(0) + noutput_items) {
			  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_id));
			  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("message_type"), pmt::from_long(1));
			  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("packet_len"), pmt::from_long(d_packet_len));
			  d_next_tag_pos += d_packet_len;
			}

		  for(int j=0;j<d_acknowledgement_end_btu.size();j++){
			  optr[noutput_items+j] = d_acknowledgement_end_btu[j];
		  }
		  noutput_items+=d_acknowledgement_end_btu.size();
		  while(d_next_tag_pos < nitems_written(0) + noutput_items) {
			  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_id));
			  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("message_type"), pmt::from_long(2));
			  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("packet_len"), pmt::from_long(d_packet_len));
			  d_next_tag_pos += d_packet_len;
			}


		d_offset = noutput_items+1;
		return noutput_items;*/
d_offset>1000;
    	if(d_offset >= d_data.size ())
		  return -1;  // Done!

		unsigned n = std::min((unsigned)d_data.size() - d_offset,
							  (unsigned)noutput_items);
		for(unsigned i = 0; i < n; i++) {
		  optr[i] = d_data[d_offset + i];
		}
		while(d_next_tag_pos < nitems_written(0) + n) {
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_id));
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("message_type"), pmt::from_long(message_type));
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("packet_len"), pmt::from_long(d_packet_len));
		  d_next_tag_pos += d_packet_len;
		}
		d_offset += n;
		return n;

		/*pmt::pmt_t dict(pmt::make_dict());
		dict = pmt::dict_add(dict, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_id));
		dict = pmt::dict_add(dict, pmt::string_to_symbol("message_type"), pmt::from_long(0));

		message_port_pub(msg_port_id, dict);
		return 400;*/
    }

  } /* namespace howto */
} /* namespace gr */

