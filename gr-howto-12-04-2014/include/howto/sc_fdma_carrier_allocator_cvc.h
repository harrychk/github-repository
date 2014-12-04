/* -*- c++ -*- */
/* 
 * Copyright 2013 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_HOWTO_SC_FDMA_CARRIER_ALLOCATOR_CVC_H
#define INCLUDED_HOWTO_SC_FDMA_CARRIER_ALLOCATOR_CVC_H

#include <howto/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace howto {

    
    class HOWTO_API sc_fdma_carrier_allocator_cvc : virtual public tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<sc_fdma_carrier_allocator_cvc> sptr;

      virtual std::string len_tag_key() = 0;
      virtual const int fft_len() = 0;
      virtual std::vector<std::vector<int> > occupied_carriers() = 0;

      /*
       * \param fft_len FFT length, is also the maximum width of the sc_fdma symbols, the
       *                output vector size and maximum value for elements in
       *                \p occupied_carriers and \p pilot_carriers.
       * \param occupied_carriers A vector of vectors of indexes. Example: if
       *                          occupied_carriers = ((1, 2, 3), (1, 2, 4)), the first
       *                          three input symbols will be mapped to carriers 1, 2
       *                          and 3. After that, a new sc_fdma symbol is started. The next
       *                          three input symbols will be placed onto carriers 1, 2
       *                          and 4 of the second sc_fdma symbol. The allocation then
       *                          starts from the beginning.
       *                          Order matters! The first input symbol is always mapped
       *                          onto occupied_carriers[0][0].
       * \param pilot_carriers The position of the pilot symbols. Same as occupied_carriers,
       *                       but the actual symbols are taken from pilot_symbols instead
       *                       of the input stream.
       * \param pilot_symbols The pilot symbols which are placed onto the pilot carriers.
       *                      pilot_symbols[0][0] is placed onto the first sc_fdma symbol, on
       *                      carrier index pilot_carriers[0][0] etc.
       * \param sync_words sc_fdma symbols that are prepended to the sc_fdma frame (usually for
       *                   synchronisation purposes, e.g. sc_fdma symbols with every second
       *                   sub-carrier being idle). Is a vector of complex vectors of length
       *                   \p fft_len
       * \param len_tag_key The key of the tag identifying the length of the input packet.
       */
      static sptr make(
	  int fft_len,
	  const std::vector<std::vector<int> > &occupied_carriers,
	  const std::string &len_tag_key = "packet_len",
	  const bool output_is_shifted=true);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_sc_fdma_CARRIER_ALLOCATOR_CVC_H */

