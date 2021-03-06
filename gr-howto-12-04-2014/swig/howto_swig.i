/* -*- c++ -*- */

#define HOWTO_API

#define ANALOG_API
#define BLOCKS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "howto_swig_doc.i"

%{
//#include "howto/square_ff.h"
//#include "howto/subcarrier_monitor.h"
#include "howto/ofdm_carrier_allocator_cvc.h"
#include "howto/ofdm_chanest_vcvc.h"
#include "howto/txt_sink.h"
#include "howto/header_payload_demux.h"
#include "howto/chan_info_parser.h"
#include "howto/ofdm_serializer_vcc.h"
#include "howto/ofdm_cyclic_prefixer.h"
#include "howto/ofdm_frame_equalizer_vcvc.h"
#include "howto/sc_fdma_frame_equalizer_vcvc.h"

#include "howto/constellation.h"
#include "howto/ofdm_equalizer_base.h"
#include "howto/ofdm_equalizer_simpledfe.h"
#include "howto/sc_fdma_equalizer_base.h"
#include "howto/sc_fdma_equalizer_simpledfe.h"
#include "howto/sc_fdma_interleaver.h"
#include "howto/sc_fdma_carrier_allocator_cvc.h"
#include "howto/symbol_decision.h"
#include "howto/packet_header_default.h"
#include "howto/packet_header_ofdm.h"
#include "howto/sc_fdma_packet_headerparser_b.h"
#include "howto/sc_fdma_packet_headergenerator_bb.h"
#include "howto/base_station_core.h"
#include "howto/user_device_core.h"
#include "howto/user_device_debug.h"
#include "howto/ofdm_outer_headerparser_bb.h"
%}

%include "howto/constellation.h"
%include "howto/ofdm_equalizer_base.h"
%include "howto/ofdm_equalizer_simpledfe.h"
%include "howto/sc_fdma_equalizer_base.h"
%include "howto/sc_fdma_equalizer_simpledfe.h"
%include "howto/packet_header_default.h"
%include "howto/packet_header_ofdm.h"
//%include "howto/square_ff.h"
//GR_SWIG_BLOCK_MAGIC2(howto, square_ff);
//%include "howto/subcarrier_monitor.h"
//GR_SWIG_BLOCK_MAGIC2(howto, subcarrier_monitor);

%include "howto/ofdm_carrier_allocator_cvc.h"
GR_SWIG_BLOCK_MAGIC2(howto, ofdm_carrier_allocator_cvc);

%include "howto/ofdm_chanest_vcvc.h"
GR_SWIG_BLOCK_MAGIC2(howto, ofdm_chanest_vcvc);
%include "howto/txt_sink.h"
GR_SWIG_BLOCK_MAGIC2(howto, txt_sink);
%include "howto/header_payload_demux.h"
GR_SWIG_BLOCK_MAGIC2(howto, header_payload_demux);
%include "howto/chan_info_parser.h"
GR_SWIG_BLOCK_MAGIC2(howto, chan_info_parser);

%include "howto/ofdm_serializer_vcc.h"
GR_SWIG_BLOCK_MAGIC2(howto, ofdm_serializer_vcc);
%include "howto/ofdm_cyclic_prefixer.h"
GR_SWIG_BLOCK_MAGIC2(howto, ofdm_cyclic_prefixer);
%include "howto/ofdm_frame_equalizer_vcvc.h"
GR_SWIG_BLOCK_MAGIC2(howto, ofdm_frame_equalizer_vcvc);
%include "howto/sc_fdma_frame_equalizer_vcvc.h"
GR_SWIG_BLOCK_MAGIC2(howto, sc_fdma_frame_equalizer_vcvc);

// Properly package up non-block object
%include "ofdm_equalizer.i"
%include "constellation.i"
%include "sc_fdma_equalizer.i"
%include "packet_header.i"

%include "howto/sc_fdma_interleaver.h"
GR_SWIG_BLOCK_MAGIC2(howto, sc_fdma_interleaver);
%include "howto/sc_fdma_carrier_allocator_cvc.h"
GR_SWIG_BLOCK_MAGIC2(howto, sc_fdma_carrier_allocator_cvc);
%include "howto/symbol_decision.h"
GR_SWIG_BLOCK_MAGIC2(howto, symbol_decision);

%include "howto/sc_fdma_packet_headerparser_b.h"
GR_SWIG_BLOCK_MAGIC2(howto, sc_fdma_packet_headerparser_b);
%include "howto/sc_fdma_packet_headergenerator_bb.h"
GR_SWIG_BLOCK_MAGIC2(howto, sc_fdma_packet_headergenerator_bb);
%include "howto/base_station_core.h"
GR_SWIG_BLOCK_MAGIC2(howto, base_station_core);
%include "howto/user_device_core.h"
GR_SWIG_BLOCK_MAGIC2(howto, user_device_core);
%include "howto/user_device_debug.h"
GR_SWIG_BLOCK_MAGIC2(howto, user_device_debug);
%include "howto/ofdm_outer_headerparser_bb.h"
GR_SWIG_BLOCK_MAGIC2(howto, ofdm_outer_headerparser_bb);
