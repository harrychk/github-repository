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
# Setup the include and linker paths
########################################################################
include_directories(
    ${GR_HOWTO_INCLUDE_DIRS}
    ${GR_BLOCKS_INCLUDE_DIRS}
    ${GR_ANALOG_INCLUDE_DIRS}
    ${GR_FFT_INCLUDE_DIRS}
    ${GR_FILTER_INCLUDE_DIRS}
    ${GR_BLOCKS_INCLUDE_DIRS}
    ${GNURADIO_RUNTIME_INCLUDE_DIRS}
    ${VOLK_INCLUDE_DIRS}
    ${LOG4CPP_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${LOG4CPP_LIBRARY_DIRS})

if(ENABLE_GR_CTRLPORT)
  ADD_DEFINITIONS(-DGR_CTRLPORT)
  include_directories(${ICE_INCLUDE_DIR})
endif(ENABLE_GR_CTRLPORT)

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND howto_sources
    ofdm_carrier_allocator_cvc_impl.cc
    ofdm_chanest_vcvc_impl.cc
    txt_sink_impl.cc
    header_payload_demux_impl.cc
    chan_info_parser_impl.cc
    ofdm_serializer_vcc_impl.cc
    ofdm_cyclic_prefixer_impl.cc
    constellation.cc
    ofdm_equalizer_base.cc
    ofdm_equalizer_simpledfe.cc
    ofdm_frame_equalizer_vcvc_impl.cc
    sc_fdma_equalizer_base.cc
    sc_fdma_equalizer_simpledfe.cc
    sc_fdma_frame_equalizer_vcvc_impl.cc
    sc_fdma_interleaver_impl.cc
    sc_fdma_carrier_allocator_cvc_impl.cc
    symbol_decision_impl.cc
    packet_header_default.cc
    packet_header_ofdm.cc
    sc_fdma_packet_headerparser_b_impl.cc
    sc_fdma_packet_headergenerator_bb_impl.cc
    base_station_core_impl.cc
    user_device_core_impl.cc
    user_device_debug_impl.cc
    ofdm_outer_headerparser_bb_impl.cc )

add_library(gnuradio-howto SHARED ${howto_sources})
target_link_libraries(gnuradio-howto ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES})
set_target_properties(gnuradio-howto PROPERTIES DEFINE_SYMBOL "gnuradio_howto_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-howto
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_howto_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_howto.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_howto.cc
)

add_executable(test-howto ${test_howto_sources})

target_link_libraries(
  test-howto
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-howto
)

GR_ADD_TEST(test_howto test-howto)
