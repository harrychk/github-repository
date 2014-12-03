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

#ifndef INCLUDED_HOWTO_SC_FDMA_INTERLEAVER_IMPL_H
#define INCLUDED_HOWTO_SC_FDMA_INTERLEAVER_IMPL_H

#include <howto/sc_fdma_interleaver.h>

namespace gr {
  namespace howto {

    class sc_fdma_interleaver_impl : public sc_fdma_interleaver
    {
     private:
	int d_lower_fft_len;
	int d_upper_fft_len;
	bool d_forward;
	const std::vector<std::vector<gr_complex> > d_sync_words;

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      sc_fdma_interleaver_impl(
	int lower_fft_len,
	int upper_fft_len,
	bool forward,
	const std::vector<std::vector<gr_complex> > &sync_words,
	const std::string &len_tag_key
      );
      ~sc_fdma_interleaver_impl();

      // Where all the action really happens
      int work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_SC_FDMA_INTERLEAVER_IMPL_H */

