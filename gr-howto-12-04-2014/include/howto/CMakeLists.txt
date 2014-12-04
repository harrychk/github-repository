# Copyright 2011,2012 Free Software Foundation, Inc.
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

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    ofdm_carrier_allocator_cvc.h
    ofdm_chanest_vcvc.h
    txt_sink.h
    header_payload_demux.h
    chan_info_parser.h
    ofdm_serializer_vcc.h
    ofdm_cyclic_prefixer.h
    constellation.h
    metric_type.h
    ofdm_equalizer_base.h
    ofdm_equalizer_simpledfe.h
    ofdm_frame_equalizer_vcvc.h
    sc_fdma_equalizer_base.h
    sc_fdma_equalizer_simpledfe.h
    sc_fdma_frame_equalizer_vcvc.h
    sc_fdma_interleaver.h
    sc_fdma_carrier_allocator_cvc.h
    symbol_decision.h
    packet_header_default.h
    packet_header_ofdm.h
    sc_fdma_packet_headerparser_b.h
    sc_fdma_packet_headergenerator_bb.h
    base_station_core.h
    user_device_core.h
    user_device_debug.h
    ofdm_outer_headerparser_bb.h DESTINATION include/howto
)
