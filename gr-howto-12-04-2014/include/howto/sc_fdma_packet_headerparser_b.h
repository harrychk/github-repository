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


#ifndef INCLUDED_HOWTO_SC_FDMA_PACKET_HEADERPARSER_B_H
#define INCLUDED_HOWTO_SC_FDMA_PACKET_HEADERPARSER_B_H

#include <howto/api.h>
#include <gnuradio/sync_block.h>
#include <howto/packet_header_default.h>

namespace gr {
  namespace howto {

    /*!
     * \brief <+description of block+>
     * \ingroup howto
     *
     */
    class HOWTO_API sc_fdma_packet_headerparser_b : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<sc_fdma_packet_headerparser_b> sptr;

      /*!
       * \param header_formatter Header object. This should be the same as used for
       *                         packet_headergenerator_bb.
       */
      static sptr make(const gr::howto::packet_header_default::sptr &header_formatter);

      /*!
       * \param header_len Number of bytes per header
       * \param len_tag_key Length Tag Key
       */
      static sptr make(long header_len, const std::string &len_tag_key);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_SC_FDMA_PACKET_HEADERPARSER_B_H */

