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
#include "symbol_decision_impl.h"

namespace gr {
  namespace howto {

    symbol_decision::sptr
    symbol_decision::make(
	int fft_len,
	const gr::howto::constellation_sptr &constellation,
	const std::string &len_tag_key
    )
    {
      return gnuradio::get_initial_sptr
        (new symbol_decision_impl(
	  		fft_len,
			constellation,
	  		len_tag_key
      ));
    }

    /*
     * The private constructor
     */
    symbol_decision_impl::symbol_decision_impl(
	int fft_len,
	const gr::howto::constellation_sptr &constellation,
	const std::string &len_tag_key
    ) : tagged_stream_block("symbol_decision",
              io_signature::make(1, 1, sizeof(gr_complex) * fft_len),
              io_signature::make(1, 1, sizeof(gr_complex) * fft_len), len_tag_key),
	d_fft_len(fft_len),
	d_constellation(constellation)
    {
	set_relative_rate(1.0);
    }

    /*
     * Our virtual destructor.
     */
    symbol_decision_impl::~symbol_decision_impl()
    {
    }

    int
    symbol_decision_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = ninput_items[0];
      return noutput_items ;
    }

    int
    symbol_decision_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      gr_complex sym_eq, sym_est;
      
      noutput_items = ninput_items[0];
      for (int i = 0; i < noutput_items; i++) {
	for (int k = 0; k < d_fft_len; k++) {
	    sym_eq = in[i*d_fft_len+k];
	    d_constellation->map_to_points(d_constellation->decision_maker(&sym_eq), &sym_est);
	    out[i*d_fft_len+k] = sym_est;
        }
      }
      
      return noutput_items;
    }

  } /* namespace howto */
} /* namespace gr */

