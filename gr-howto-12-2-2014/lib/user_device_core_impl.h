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

#ifndef INCLUDED_HOWTO_USER_DEVICE_CORE_IMPL_H
#define INCLUDED_HOWTO_USER_DEVICE_CORE_IMPL_H

#include <howto/user_device_core.h>
#include <time.h>

namespace gr {
  namespace howto {

    class user_device_core_impl : public user_device_core
    {
     private:
      // Nothing to declare in this block.
    	unsigned int d_device_id; //should be IMEI
    	unsigned int d_packet_len;
    	unsigned int d_next_tag_pos;
    	int d_state;
    	clock_t d_time_start;
    	long d_consumed_time;

    	// user device sends request_utb to basestation
    	std::vector<unsigned char> d_request_utb;

    	// the acknowledgement that basestation sends to user device after receiving the request_utb
    	std::vector<unsigned char> d_acknowledgement_btu;

    	// the acknowledgement that user device sends to basestation after receiving the incoming acknowledgement
    	std::vector<unsigned char> d_acknowledgement_utb;

    	// the acknowledgement that basestation sends to user device after finishing transmitting data
		std::vector<unsigned char> d_acknowledgement_end_btu;

		// the acknowledgement that user device sends to basestation after receiving the incoming end acknowledgement
		std::vector<unsigned char> d_acknowledgement_end_utb;

    	void copy_data(std::vector<unsigned char> &data, unsigned char *out, unsigned int message_type);
    	int get_message_type(std::vector<tag_t> &tags);
    	bool check_ack(const unsigned char *received_ack,std::vector<unsigned char> &ref_ack);

     public:
      user_device_core_impl(
    		  const unsigned int device_id,
			  const unsigned int packet_len,
			  const std::vector<unsigned char> &request_utb,
			  const std::vector<unsigned char> &acknowledgement_btu,
			  const std::vector<unsigned char> &acknowledgement_utb,
			  const std::vector<unsigned char> &acknowledgement_end_btu,
			  const std::vector<unsigned char> &acknowledgement_end_utb);
      ~user_device_core_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_USER_DEVICE_CORE_IMPL_H */

