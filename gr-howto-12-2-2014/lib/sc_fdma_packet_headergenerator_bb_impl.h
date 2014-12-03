/* -*- c++ -*- */
/* Copyright 2012 Free Software Foundation, Inc.
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

#ifndef INCLUDED_HOWTO_SC_FDMA_PACKET_HEADERGENERATOR_bb_IMPL_H
#define INCLUDED_HOWTO_SC_FDMA_PACKET_HEADERGENERATOR_bb_IMPL_H

#include <howto/sc_fdma_packet_headergenerator_bb.h>

namespace gr {
  namespace howto {

    class sc_fdma_packet_headergenerator_bb_impl : public sc_fdma_packet_headergenerator_bb
    {
     private:
      gr::howto::packet_header_default::sptr d_formatter;

     public:
      sc_fdma_packet_headergenerator_bb_impl(
	  const packet_header_default::sptr &header_formatter,
	  const std::string &len_tag_key
      );
      ~sc_fdma_packet_headergenerator_bb_impl();

      void remove_length_tags(const std::vector<std::vector<tag_t> > &tags) {};
      int calculate_output_stream_length(const gr_vector_int &ninput_items) { return d_formatter->header_len(); };

      int work(int noutput_items,
	  gr_vector_int &ninput_items,
	  gr_vector_const_void_star &input_items,
	  gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_howto_sc_fdma_packet_headergenerator_bb_IMPL_H */

