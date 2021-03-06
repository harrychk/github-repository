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


#ifndef INCLUDED_HOWTO_SC_FDMA_INTERLEAVER_H
#define INCLUDED_HOWTO_SC_FDMA_INTERLEAVER_H

#include <howto/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace howto {

    /*!
     * \brief <+description of block+>
     * \ingroup howto
     *
     */
    class HOWTO_API sc_fdma_interleaver : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<sc_fdma_interleaver> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of howto::sc_fdma_interleaver.
       *
       * To avoid accidental use of raw pointers, howto::sc_fdma_interleaver's
       * constructor is in a private implementation
       * class. howto::sc_fdma_interleaver::make is the public interface for
       * creating new instances.
       */
      static sptr make(
	int lower_fft_len,
	int upper_fft_len,
	bool forward,
	const std::vector<std::vector<gr_complex> > &sync_words,
	const std::string &len_tag_key="packet_len"
      );
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_SC_FDMA_INTERLEAVER_H */

