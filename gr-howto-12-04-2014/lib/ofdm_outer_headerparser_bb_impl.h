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

#ifndef INCLUDED_HOWTO_OFDM_OUTER_HEADERPARSER_BB_IMPL_H
#define INCLUDED_HOWTO_OFDM_OUTER_HEADERPARSER_BB_IMPL_H

#include <howto/ofdm_outer_headerparser_bb.h>
#include <howto/constellation.h>

namespace gr {
  namespace howto {

    class ofdm_outer_headerparser_bb_impl : public ofdm_outer_headerparser_bb
    {
     private:
        gr::howto::constellation_sptr d_constellation;
		int d_fft_len;
		std::vector<std::vector<int> > d_occupied_carriers;
		//std::vector<int> &d_occupied_carriers_total;

		int check_pid_index(int pid, std::vector<char> &pid_buffer);
		bool check_pid(char pid);

     public:
      ofdm_outer_headerparser_bb_impl(int fft_len, const std::vector<std::vector<int> > &occupied_carriers);
      ~ofdm_outer_headerparser_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_OFDM_OUTER_HEADERPARSER_BB_IMPL_H */

