# Install script for directory: /home/chk/out-of-tree/gr-howto/grc

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/chk/out-of-tree/gr-howto/grc/howto_ofdm_carrier_allocator_cvc.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_ofdm_chanest_vcvc.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_txt_sink.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_header_payload_demux.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_chan_info_parser.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_ofdm_serializer_vcc.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_ofdm_cyclic_prefixer.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_ofdm_frame_equalizer_vcvc.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_sc_fdma_frame_equalizer_vcvc.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_sc_fdma_interleaver.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_sc_fdma_deinterleaver.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_sc_fdma_carrier_allocator_cvc.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_symbol_decision.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_sc_fdma_packet_headerparser_b.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_sc_fdma_packet_headergenerator_bb.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_base_station_core.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_user_device_core.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_user_device_debug.xml"
    "/home/chk/out-of-tree/gr-howto/grc/howto_ofdm_outer_headerparser_bb.xml"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

