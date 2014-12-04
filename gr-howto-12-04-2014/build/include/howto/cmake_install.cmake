# Install script for directory: /home/chk/out-of-tree/gr-howto/include/howto

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/howto" TYPE FILE FILES
    "/home/chk/out-of-tree/gr-howto/include/howto/api.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_carrier_allocator_cvc.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_chanest_vcvc.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/txt_sink.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/header_payload_demux.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/chan_info_parser.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_serializer_vcc.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_cyclic_prefixer.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/constellation.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/metric_type.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_equalizer_base.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_equalizer_simpledfe.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_frame_equalizer_vcvc.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_equalizer_base.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_equalizer_simpledfe.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_frame_equalizer_vcvc.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_interleaver.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_carrier_allocator_cvc.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/symbol_decision.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/packet_header_default.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/packet_header_ofdm.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_packet_headerparser_b.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/sc_fdma_packet_headergenerator_bb.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/base_station_core.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/user_device_core.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/user_device_debug.h"
    "/home/chk/out-of-tree/gr-howto/include/howto/ofdm_outer_headerparser_bb.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

