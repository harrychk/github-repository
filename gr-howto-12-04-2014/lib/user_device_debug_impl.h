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

#ifndef INCLUDED_HOWTO_USER_DEVICE_DEBUG_IMPL_H
#define INCLUDED_HOWTO_USER_DEVICE_DEBUG_IMPL_H

#include <howto/user_device_debug.h>
#include <time.h>

namespace gr {
  namespace howto {

    class user_device_debug_impl : public user_device_debug
    {
     private:
      // Nothing to declare in this block.
    	unsigned int d_device_id; //should be IMEI
		unsigned int d_packet_len;
		unsigned int d_next_tag_pos;
		std::vector<unsigned char> d_data;
		unsigned int d_offset;
		clock_t d_time_start;

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

     public:
      user_device_debug_impl(
    		  const std::vector<unsigned char> &data,
    		const unsigned int device_id,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb);
      ~user_device_debug_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_USER_DEVICE_DEBUG_IMPL_H */

