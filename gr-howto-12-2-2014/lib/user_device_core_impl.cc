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
#include "user_device_core_impl.h"

namespace gr {
  namespace howto {

    enum demux_states_t {
    	STATE_SEND_REQUEST,       	// send request with device id and message type=0
		STATE_CHECK_ACK,            // check ack from BS, if fails, send request again
		STATE_SEND_ACK,       		// send ack to BS, prepare for receiving data
		STATE_RECEIVE_DATA,  		// receive data, if time out, send ack again
    };

    user_device_core::sptr
    user_device_core::make(
    		const unsigned int device_id,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb)
    {
      return gnuradio::get_initial_sptr
        (new user_device_core_impl(device_id, packet_len, request_utb, acknowledgement_btu, acknowledgement_utb,
        		acknowledgement_end_btu, acknowledgement_end_utb));
    }

    /*
     * The private constructor
     */
    user_device_core_impl::user_device_core_impl(
    		const unsigned int device_id,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb
		) : block("user_device_core",
              io_signature::make(1, 1, sizeof(char)),
              io_signature::make(1, 1, sizeof(char))),
			d_device_id(device_id),
			d_packet_len(packet_len),
			d_request_utb(request_utb),
			d_acknowledgement_btu(acknowledgement_btu),
    		d_acknowledgement_utb(acknowledgement_utb),
			d_acknowledgement_end_btu(acknowledgement_end_btu),
			d_acknowledgement_end_utb(acknowledgement_end_utb),
			d_next_tag_pos(0),
			d_consumed_time(0),
			//d_state(STATE_SEND_REQUEST)
			d_state(STATE_RECEIVE_DATA) // debug use
    {
    	set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    user_device_core_impl::~user_device_core_impl()
    {
    }

    void
    user_device_core_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    user_device_core_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
    	const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        int message_type = -1;
        // get incoming tags
		std::vector<tag_t> tags;
		get_tags_in_range(
			tags, 0,
			nitems_read(0),
			nitems_read(0) + d_packet_len
		);

        switch (d_state) {
        case STATE_SEND_REQUEST:
			copy_data(d_request_utb, out, 0); // message type = 0 (request)
			produce(0, d_request_utb.size());


			d_state = STATE_CHECK_ACK;
			//d_next_tag_pos = 0;
			d_time_start = clock();
			break;

        case STATE_CHECK_ACK:
        	if((clock()-d_time_start)/CLOCKS_PER_SEC >= 5){ // 5 seconds time out
        		consume_each(ninput_items[0]);
        		d_state = STATE_SEND_REQUEST;
        		break;
        	}else if(get_message_type(tags) != 0){ // ack from BS
        		consume_each(ninput_items[0]);
        		break;
        	}else{
        		if(check_ack(in, d_acknowledgement_btu)){
					consume_each(ninput_items[0]);
					d_state = STATE_SEND_ACK;
				}else{
					consume_each(ninput_items[0]);
					break;
				}
        	}
        	// fall through


        case STATE_SEND_ACK:
        	copy_data(d_acknowledgement_utb, out, 1); // message type = 1 (ack1)
			produce(0, d_acknowledgement_utb.size());

			d_state = STATE_RECEIVE_DATA;
			//d_next_tag_pos = 0;
			d_time_start = clock();
			break;


        case STATE_RECEIVE_DATA:

        	if(d_consumed_time ==15){ // 15 seconds time out, resend request
        		consume_each(ninput_items[0]);
				d_state = STATE_SEND_REQUEST;
				d_consumed_time=0;
				break;
        	}
			if((clock()-d_time_start)/CLOCKS_PER_SEC >= 5){ // 5 seconds time out, send ack
				d_consumed_time+=5;
				consume_each(ninput_items[0]);
				d_state = STATE_SEND_ACK;
				break;
			}

			for(unsigned i = 0; i< ninput_items[0]/d_packet_len; i++){
				get_tags_in_range(
					tags, 0,
					nitems_read(0) + d_packet_len*i,
					nitems_read(0) + d_packet_len*(i+1)
				);
				message_type = get_message_type(tags);

				if(message_type == 1){
					//receive data
					std::cout<<"U";
					consume_each(d_packet_len);
					break;
				}else if (message_type == 2){
					if(check_ack(in, d_acknowledgement_end_btu)){
						copy_data(d_acknowledgement_end_utb, out, 2); // message type = 2 (ack2, respond data end)
						produce(0, d_acknowledgement_end_utb.size());
						consume_each(ninput_items[0]);

						d_state = STATE_SEND_REQUEST;
						sleep(2000);
						//d_next_tag_pos = 0;
						break;
					}else{
						consume_each(ninput_items[0]);
						break;
					}
				}else{
					consume_each(ninput_items[0]);
					break;
				}

			}
			break;


        default:
        	  throw std::runtime_error("invalid state");
        }

        // Tell runtime system how many output items we produced.
        return WORK_CALLED_PRODUCE;
    }

    void
	user_device_core_impl::copy_data(std::vector<unsigned char> &data, unsigned char *out, unsigned int message_type){
    	//copy request data
		unsigned int n_out = data.size();
		for(unsigned i = 0; i < n_out; i++) {
		  out[i] = data[i];
		}

		//add tags
		while(d_next_tag_pos < nitems_written(0) + n_out) {
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_id));
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("message_type"), pmt::from_long(message_type));
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("packet_len"), pmt::from_long(d_packet_len));
		  d_next_tag_pos += d_packet_len;
		}
    }

    int
	user_device_core_impl::get_message_type(std::vector<tag_t> &tags)
	{
		if(tags.size()==0){
			return -1;
		}else{
			int message = -1;
			for (unsigned t = 0; t < tags.size(); t++) {
				if(pmt::equal(pmt::string_to_symbol("message_type"), tags[t].key)){
					message = pmt::to_long(tags[t].value);
				}
				if(pmt::equal(pmt::string_to_symbol("device_id"), tags[t].key)){ //exclude message with wrong device
					if(!pmt::equal(pmt::from_long(d_device_id), tags[t].value)){
						return -1;
					}
				}
			}
			return message;
		}
	}

    bool
	user_device_core_impl::check_ack(const unsigned char *received_ack,std::vector<unsigned char> &ref_ack)
	{
    	unsigned i = 0;
    	for(i = 0; i<100;i++){ //ack seq is 100 length
			if(received_ack[i]!=ref_ack[i]){
				break;
			}
		}
    	if(i!=100)
    		return false;
    	else
    		return true;
	}

  } /* namespace howto */
} /* namespace gr */

