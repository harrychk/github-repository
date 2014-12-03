# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    howto_ofdm_carrier_allocator_cvc.xml
    howto_ofdm_chanest_vcvc.xml
    howto_txt_sink.xml
    howto_header_payload_demux.xml
    howto_chan_info_parser.xml
    howto_ofdm_serializer_vcc.xml
    howto_ofdm_cyclic_prefixer.xml
    howto_ofdm_frame_equalizer_vcvc.xml
    howto_sc_fdma_frame_equalizer_vcvc.xml
    howto_sc_fdma_interleaver.xml
    howto_sc_fdma_deinterleaver.xml
    howto_sc_fdma_carrier_allocator_cvc.xml
    howto_symbol_decision.xml
    howto_sc_fdma_packet_headerparser_b.xml
    howto_sc_fdma_packet_headergenerator_bb.xml
    howto_base_station_core.xml
    howto_user_device_core.xml
    howto_user_device_debug.xml
    howto_ofdm_outer_headerparser_bb.xml DESTINATION share/gnuradio/grc/blocks
)
