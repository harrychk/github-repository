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


#ifndef INCLUDED_HOWTO_SC_FDMA_FRAME_EQUALIZER_VCVC_H
#define INCLUDED_HOWTO_SC_FDMA_FRAME_EQUALIZER_VCVC_H

#include <howto/api.h>

#include <howto/sc_fdma_equalizer_simpledfe.h>
#include <howto/constellation.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace howto {

    /*!
     * \brief sc_fdma frame equalizer
     * \ingroup sc_fdma_blk
     *
     * \details
     * Performs equalization in one or two dimensions on a tagged sc_fdma frame.
     *
     * This does two things:
     * First, it removes the coarse carrier offset. If a tag is found on the first
     * item with the key 'sc_fdma_sync_carr_offset', this is interpreted as the coarse
     * frequency offset in number of carriers.
     * Next, it performs equalization in one or two dimensions on a tagged sc_fdma frame.
     * The actual equalization is done by a sc_fdma_frame_equalizer object, outside of
     * the block.
     *
     * Note that the tag with the coarse carrier offset is not removed. Blocks
     * downstream from this block must not attempt to also correct this offset.
     *
     * Input: a tagged series of sc_fdma symbols.
     * Output: The same as the input, but equalized and frequency-corrected.
     */
    class HOWTO_API sc_fdma_frame_equalizer_vcvc : virtual public tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<sc_fdma_frame_equalizer_vcvc> sptr;

      /*!
       * \param equalizer The equalizer object that will do the actual work
       * \param cp_len Length of the cyclic prefix in samples (required to correct the frequency offset)
       * \param len_tag_key Length tag key
       * \param propagate_channel_state If true, the channel state after the last symbol
       *                                will be added to the first symbol as a tag
       * \param fixed_frame_len Set if the frame length is fixed throughout, 
       *                        helps with book keeping.
       */
      static sptr make(
	   sc_fdma_equalizer_base::sptr equalizer,
	   int cp_len,
	   const std::string &len_tag_key = "frame_len",
	   bool propagate_channel_state=false,
	   int fixed_frame_len=0
      );
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_sc_fdma_FRAME_EQUALIZER_VCVC_H */

