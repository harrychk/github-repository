
/*
 * This file was automatically generated using swig_doc.py.
 *
 * Any changes to it will be lost next time it is regenerated.
 */




%feature("docstring") gr::howto::base_station_core "<+description of block+>"

%feature("docstring") gr::howto::base_station_core::make "Return a shared_ptr to a new instance of howto::base_station_core.

To avoid accidental use of raw pointers, howto::base_station_core's constructor is in a private implementation class. howto::base_station_core::make is the public interface for creating new instances.

Params: (data, packet_len, request_utb, acknowledgement_btu, acknowledgement_utb, acknowledgement_end_btu, acknowledgement_end_utb)"

%feature("docstring") gr::howto::chan_info_parser "<+description of block+>"

%feature("docstring") gr::howto::chan_info_parser::make "Return a shared_ptr to a new instance of howto::chan_info_parser.

To avoid accidental use of raw pointers, howto::chan_info_parser's constructor is in a private implementation class. howto::chan_info_parser::make is the public interface for creating new instances.

Params: (fft_len)"

%feature("docstring") gr::howto::constellation "An abstracted constellation object.

The constellation objects hold the necessary information to pass around constellation information for modulators and demodulators. These objects contain the mapping between the bits and the constellation points used to represent them as well as methods for slicing the symbol space. Various implementations are possible for efficiency and ease of use.

Standard constellations (BPSK, QPSK, QAM, etc) can be inherited from this class and overloaded to perform optimized slicing and constellation mappings."

%feature("docstring") gr::howto::constellation::constellation "

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality)"

%feature("docstring") gr::howto::constellation::~constellation "

Params: (NONE)"

%feature("docstring") gr::howto::constellation::map_to_points "Returns the constellation points for a symbol value.

Params: (value, points)"

%feature("docstring") gr::howto::constellation::map_to_points_v "

Params: (value)"

%feature("docstring") gr::howto::constellation::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation::decision_maker_v "Takes a vector rather than a pointer. Better for SWIG wrapping.

Params: (sample)"

%feature("docstring") gr::howto::constellation::decision_maker_pe "Also calculates the phase error.

Params: (sample, phase_error)"

%feature("docstring") gr::howto::constellation::calc_metric "Calculates distance.

Calculates metrics for all points in the constellation. For use with the viterbi algorithm.

Params: (sample, metric, type)"

%feature("docstring") gr::howto::constellation::calc_euclidean_metric "

Params: (sample, metric)"

%feature("docstring") gr::howto::constellation::calc_hard_symbol_metric "

Params: (sample, metric)"

%feature("docstring") gr::howto::constellation::points "Returns the set of points in this constellation.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::s_points "Returns the vector of points in this constellation. Raise error if dimensionality is not one.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::v_points "Returns a vector of vectors of points.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::apply_pre_diff_code "Whether to apply an encoding before doing differential encoding. (e.g. gray coding)

Params: (NONE)"

%feature("docstring") gr::howto::constellation::set_pre_diff_code "Whether to apply an encoding before doing differential encoding. (e.g. gray coding)

Params: (a)"

%feature("docstring") gr::howto::constellation::pre_diff_code "Returns the encoding to apply before differential encoding.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::rotational_symmetry "Returns the order of rotational symmetry.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::dimensionality "Returns the number of complex numbers in a single symbol.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::bits_per_symbol "

Params: (NONE)"

%feature("docstring") gr::howto::constellation::arity "

Params: (NONE)"

%feature("docstring") gr::howto::constellation::base "

Params: (NONE)"

%feature("docstring") gr::howto::constellation::as_pmt "

Params: (NONE)"

%feature("docstring") gr::howto::constellation::gen_soft_dec_lut "Generates the soft decision LUT based on constellation and symbol map.

Generates the soft decision LUT based on constellation and symbol map. It can be given a estimate of the noise power in the channel as .


This is expensive to compute.

Params: (precision, npwr)"

%feature("docstring") gr::howto::constellation::calc_soft_dec "Calculate soft decisions for the given .

Calculate the soft decisions from the given  at the given noise power .

This is a very costly algorithm (especially for higher order modulations) and should be used sparingly. It uses the gen_soft_dec_lut function to generate the LUT, which should be done once or if a large change in the noise floor is detected.

Instead of using this function, generate the LUT using the gen_soft_dec_lut after creating the constellation object and then use the soft_decision_maker function to return the answer from the LUT.

Params: (sample, npwr)"

%feature("docstring") gr::howto::constellation::set_soft_dec_lut "Define a soft decision look-up table.

Define a soft decision look-up table (LUT). Because soft decisions can be calculated in various ways with various levels of accuracy and complexity, this function allows users to create a LUT in their own way.

Setting the LUT here means that has_soft_dec_lut will return true. Decision vectors returned by soft_decision_maker will be calculated using this LUT.

Params: (soft_dec_lut, precision)"

%feature("docstring") gr::howto::constellation::has_soft_dec_lut "Returns True if the soft decision LUT has been defined, False otherwise.

Params: (NONE)"

%feature("docstring") gr::howto::constellation::soft_decision_maker "Returns the soft decisions for the given .

Returns the soft decisions for the given . If a LUT is defined for the object, the decisions will be calculated from there. Otherwise, this function will call calc_soft_dec directly to calculate the soft decisions.

Params: (sample)"

%feature("docstring") gr::howto::constellation::get_distance "

Params: (index, sample)"

%feature("docstring") gr::howto::constellation::get_closest_point "

Params: (sample)"

%feature("docstring") gr::howto::constellation::calc_arity "

Params: (NONE)"

%feature("docstring") gr::howto::constellation::max_min_axes "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_8psk "HOWTO constellation for 8PSK."

%feature("docstring") gr::howto::constellation_8psk::make "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_8psk::~constellation_8psk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_8psk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation_8psk::constellation_8psk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_bpsk "HOWTO constellation for BPSK ."

%feature("docstring") gr::howto::constellation_bpsk::make "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_bpsk::~constellation_bpsk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_bpsk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation_bpsk::constellation_bpsk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_calcdist "Calculate Euclidian distance for any constellation.

Constellation which calculates the distance to each point in the constellation for decision making. Inefficient for large constellations."

%feature("docstring") gr::howto::constellation_calcdist::make "Make a general constellation object that calculates the Euclidean distance for hard decisions.

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality)"

%feature("docstring") gr::howto::constellation_calcdist::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation_calcdist::constellation_calcdist "

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality)"

%feature("docstring") gr::howto::constellation_dqpsk "HOWTO constellation for DQPSK."

%feature("docstring") gr::howto::constellation_dqpsk::make "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_dqpsk::~constellation_dqpsk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_dqpsk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation_dqpsk::constellation_dqpsk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_expl_rect "Rectangular HOWTO constellation.

Only implemented for 1-(complex)dimensional constellation.

Constellation space is divided into rectangular sectors. Each sector is associated with the nearest constellation point.

This class is different from constellation_rect in that the mapping from sector to constellation point is explicitly passed into the constructor as sector_values. Usually we do not need this, since we want each sector to be automatically mapped to the closest constellation point, however sometimes it's nice to have the flexibility."

%feature("docstring") gr::howto::constellation_expl_rect::make "

Params: (constellation, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors, sector_values)"

%feature("docstring") gr::howto::constellation_expl_rect::~constellation_expl_rect "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_expl_rect::constellation_expl_rect "

Params: (constellation, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors, sector_values)"

%feature("docstring") gr::howto::constellation_expl_rect::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::howto::constellation_psk "constellation_psk

Constellation space is divided into pie slices sectors.

Each slice is associated with the nearest constellation point.

Works well for PSK but nothing else.

Assumes that there is a constellation point at 1.x"

%feature("docstring") gr::howto::constellation_psk::make "

Params: (constell, pre_diff_code, n_sectors)"

%feature("docstring") gr::howto::constellation_psk::~constellation_psk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_psk::get_sector "

Params: (sample)"

%feature("docstring") gr::howto::constellation_psk::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::howto::constellation_psk::constellation_psk "

Params: (constell, pre_diff_code, n_sectors)"

%feature("docstring") gr::howto::constellation_qpsk "HOWTO constellation for QPSK."

%feature("docstring") gr::howto::constellation_qpsk::make "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_qpsk::~constellation_qpsk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_qpsk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation_qpsk::constellation_qpsk "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_rect "Rectangular HOWTO constellation

Only implemented for 1-(complex)dimensional constellation.

Constellation space is divided into rectangular sectors. Each sector is associated with the nearest constellation point.

Works well for square QAM.

Works for any generic constellation provided sectors are not too large."

%feature("docstring") gr::howto::constellation_rect::make "Make a rectangular constellation object.

Params: (constell, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors)"

%feature("docstring") gr::howto::constellation_rect::~constellation_rect "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_rect::constellation_rect "

Params: (constell, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors)"

%feature("docstring") gr::howto::constellation_rect::get_sector "

Params: (sample)"

%feature("docstring") gr::howto::constellation_rect::calc_sector_center "

Params: (sector)"

%feature("docstring") gr::howto::constellation_rect::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::howto::constellation_sector "Sectorized HOWTO constellation.

constellation_sector

Constellation space is divided into sectors. Each sector is associated with the nearest constellation point."

%feature("docstring") gr::howto::constellation_sector::constellation_sector "Make a sectorized constellation object.

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality, n_sectors)"

%feature("docstring") gr::howto::constellation_sector::~constellation_sector "

Params: (NONE)"

%feature("docstring") gr::howto::constellation_sector::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::howto::constellation_sector::get_sector "

Params: (sample)"

%feature("docstring") gr::howto::constellation_sector::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::howto::constellation_sector::find_sector_values "

Params: (NONE)"

%feature("docstring") gr::howto::header_payload_demux "Header/Payload demuxer.

This block is designed to handle packets from a bursty transmission. Input 0 takes a continuous transmission of samples. If used, input 1 is a trigger signal. In this case, a 1 on input 1 is a trigger. Otherwise, a tag with the key specified in  is used as a trigger (its value is irrelevant).

Until a trigger signal is detected, all samples are dropped onto the floor. Once a trigger is detected, a total of  items are copied to output 0. The block then stalls until it receives a message on the message port . The message must be a PMT dictionary; all key/value pairs are copied as tags to the first item of the payload (which is assumed to be the first item after the header). The value corresponding to the key specified in  is read and taken as the payload length. The payload, together with the header data as tags, is then copied to output 1.

If specified,  items are discarded before every symbol. This is useful for demuxing bursts of OFDM signals.

Any tags on the input stream are copied to the corresponding output  they're on an item that is propagated. Note that a tag on the header items is copied to the header stream; that means the header-parsing block must handle these tags if they should go on the payload. A special case are tags on items that make up the guard interval. These are copied to the first item of the following symbol."

%feature("docstring") gr::howto::header_payload_demux::make "

Params: (header_len, items_per_symbol, guard_interval, length_tag_key, trigger_tag_key, output_symbols, itemsize, timing_tag_key, samp_rate, special_tags)"

%feature("docstring") gr::howto::ofdm_carrier_allocator_cvc "Create frequency domain OFDM symbols from complex values, add pilots.

This block turns a stream of complex, scalar modulation symbols into vectors which are the input for an IFFT in an OFDM transmitter. It also supports the possibility of placing pilot symbols onto the carriers.

The carriers can be allocated freely, if a carrier is not allocated, it is set to zero. This allows doing OFDMA-style carrier allocations.

Input: A tagged stream of complex scalars. The first item must have a tag containing the number of complex symbols in this frame. Output: A tagged stream of complex vectors of length fft_len. This can directly be connected to an FFT block. Make sure to set this block to 'reverse' for the IFFT. If  is true, the FFT block must activate FFT shifting, otherwise, set shifting to false. If given, sync words are prepended to the output. Note that sync words are prepended verbatim, make sure they are shifted (or not).

Carrier indexes are always such that index 0 is the DC carrier (note: you should not allocate this carrier). The carriers below the DC carrier are either indexed with negative numbers, or with indexes larger than . Index -1 and index  both identify the carrier below the DC carrier.

Tags are propagated such that a tag on an incoming complex symbol is mapped to the corresponding OFDM symbol. There is one exception: If a tag is on the first OFDM symbol, it is assumed that this tag should stay there, so it is moved to the front even if a sync word is included (any other tags will never be attached to the sync word). This allows tags to control the transmit timing to pass through in the correct position."

%feature("docstring") gr::howto::ofdm_carrier_allocator_cvc::len_tag_key "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_carrier_allocator_cvc::fft_len "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_carrier_allocator_cvc::occupied_carriers "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_carrier_allocator_cvc::pilot_carriers "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_carrier_allocator_cvc::make "

Params: (num_user, total_power, bandwidth, noise_density, fft_len, occupied_carriers, pilot_carriers, pilot_symbols, sync_words, len_tag_key, output_is_shifted)"

%feature("docstring") gr::howto::ofdm_chanest_vcvc "Estimate channel and coarse frequency offset for OFDM from preambles

Input: OFDM symbols (in frequency domain). The first one (or two) symbols are expected to be synchronisation symbols, which are used to estimate the coarse freq offset and the initial equalizer taps (these symbols are removed from the stream). The following  are passed through unmodified (the actual equalisation must be done elsewhere). Output: The data symbols, without the synchronisation symbols. The first data symbol passed through has two tags: 'ofdm_sync_carr_offset' (integer), the coarse frequency offset as number of carriers, and 'ofdm_sync_eq_taps' (complex vector). Any tags attached to the synchronisation symbols are attached to the first data symbol. All other tags are propagated as expected.

Note: The vector on ofdm_sync_eq_taps is already frequency-corrected, whereas the rest is not.

This block assumes the frequency offset is even (i.e. an integer multiple of 2).

[1] Schmidl, T.M. and Cox, D.C., \"Robust frequency and timing synchronization for OFDM\", Communications, IEEE Transactions on, 1997. [2] K.D. Kammeyer, \"Nachrichtenuebertragung,\" Chapter. 16.3.2."

%feature("docstring") gr::howto::ofdm_chanest_vcvc::make "

Params: (sync_symbol1, sync_symbol2, n_data_symbols, eq_noise_red_len, max_carr_offset, force_one_sync_symbol)"

%feature("docstring") gr::howto::ofdm_cyclic_prefixer "Adds a cyclic prefix and performs pulse shaping on OFDM symbols.

Input: OFDM symbols (in the time domain, i.e. after the IFFT). Optionally, entire frames can be processed. In this case,  must be specified which holds the key of the tag that denotes how many OFDM symbols are in a frame. Output: A stream of (scalar) complex symbols, which include the cyclic prefix and the pulse shaping. Note: If complete frames are processed, and  is greater than zero, the final OFDM symbol is followed by the delay line of the pulse shaping.

The pulse shape is a raised cosine in the time domain."

%feature("docstring") gr::howto::ofdm_cyclic_prefixer::make "

Params: (input_size, output_size, rolloff_len, len_tag_key)"



%feature("docstring") gr::howto::ofdm_equalizer_1d_pilots::ofdm_equalizer_1d_pilots "

Params: (fft_len, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, input_is_shifted)"

%feature("docstring") gr::howto::ofdm_equalizer_1d_pilots::~ofdm_equalizer_1d_pilots "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_equalizer_1d_pilots::reset "Reset the channel information state knowledge.

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_equalizer_1d_pilots::get_channel_state "Return the current channel state.

Params: (taps)"



%feature("docstring") gr::howto::ofdm_equalizer_base::ofdm_equalizer_base "

Params: (fft_len)"

%feature("docstring") gr::howto::ofdm_equalizer_base::~ofdm_equalizer_base "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_equalizer_base::reset "Reset the channel information state knowledge.

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_equalizer_base::equalize "Run the actual equalization.

Params: (frame, n_sym, n_symbol, start_pos, initial_taps, tags)"

%feature("docstring") gr::howto::ofdm_equalizer_base::get_channel_state "Return the current channel state.

Params: (taps)"

%feature("docstring") gr::howto::ofdm_equalizer_base::fft_len "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_equalizer_base::base "

Params: (NONE)"



%feature("docstring") gr::howto::ofdm_equalizer_simpledfe::ofdm_equalizer_simpledfe "

Params: (fft_len, constellation, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, alpha, input_is_shifted)"

%feature("docstring") gr::howto::ofdm_equalizer_simpledfe::~ofdm_equalizer_simpledfe "

Params: (NONE)"

%feature("docstring") gr::howto::ofdm_equalizer_simpledfe::equalize "Run the actual equalization.

Params: (frame, n_sym, n_symbol, start_pos, initial_taps, tags)"

%feature("docstring") gr::howto::ofdm_equalizer_simpledfe::make "

Params: (fft_len, constellation, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, alpha, input_is_shifted)"

%feature("docstring") gr::howto::ofdm_frame_equalizer_vcvc "OFDM frame equalizer.

Performs equalization in one or two dimensions on a tagged OFDM frame.

This does two things: First, it removes the coarse carrier offset. If a tag is found on the first item with the key 'ofdm_sync_carr_offset', this is interpreted as the coarse frequency offset in number of carriers. Next, it performs equalization in one or two dimensions on a tagged OFDM frame. The actual equalization is done by a ofdm_frame_equalizer object, outside of the block.

Note that the tag with the coarse carrier offset is not removed. Blocks downstream from this block must not attempt to also correct this offset.

Input: a tagged series of OFDM symbols. Output: The same as the input, but equalized and frequency-corrected."

%feature("docstring") gr::howto::ofdm_frame_equalizer_vcvc::make "

Params: (fft_len, device_id, pilot_carriers, pilot_symbols, cp_len, len_tag_key, propagate_channel_state, fixed_frame_len)"

%feature("docstring") gr::howto::ofdm_outer_headerparser_bb "<+description of block+>"

%feature("docstring") gr::howto::ofdm_outer_headerparser_bb::make "Return a shared_ptr to a new instance of howto::ofdm_outer_headerparser_bb.

To avoid accidental use of raw pointers, howto::ofdm_outer_headerparser_bb's constructor is in a private implementation class. howto::ofdm_outer_headerparser_bb::make is the public interface for creating new instances.

Params: (fft_len, occupied_carriers)"

%feature("docstring") gr::howto::ofdm_serializer_vcc "Serializes complex modulations symbols from OFDM sub-carriers.

This is the inverse block to the carrier_allocator_cvc. It outputs the complex data symbols as a tagged stream, discarding the pilot symbols.

If given, two different tags are parsed: The first key () specifies the number of OFDM symbols in the frame at the input. The second key () specifies the number of complex symbols that are coded into this frame. If given, this second key is then used at the output, otherwise,  is used. If both are given, the packet length specifies the maximum number of output items, and the frame length specifies the exact number of consumed input items.

It is possible to correct a carrier offset in this function by passing another tag with said offset.

Input: Complex vectors of length  Output: Complex scalars, in the same order as specified in occupied_carriers."

%feature("docstring") gr::howto::ofdm_serializer_vcc::make "

Params: (fft_len, len_tag_key, packet_len_tag_key, symbols_skipped, carr_offset_key, input_is_shifted)"

%feature("docstring") gr::howto::packet_header_default "Default header formatter for howto packet transmission.

For bursty/packetized howto transmission, packets are usually prepended with a packet header, containing the number of bytes etc. This class is not a block, but a tool to create these packet header.

This is a default packet header (see header_formatter()) for a description on the header format). To create other header, derive packet header creator classes from this function.

gr::howto::packet_headergenerator_bb uses header generators derived from this class to create packet headers from data streams."

%feature("docstring") gr::howto::packet_header_default::packet_header_default "

Params: (header_len, len_tag_key, num_tag_key, device_id_tag_key, message_type_tag_key, bits_per_byte)"

%feature("docstring") gr::howto::packet_header_default::~packet_header_default "

Params: (NONE)"

%feature("docstring") gr::howto::packet_header_default::base "

Params: (NONE)"

%feature("docstring") gr::howto::packet_header_default::formatter "

Params: (NONE)"

%feature("docstring") gr::howto::packet_header_default::set_header_num "

Params: (header_num)"

%feature("docstring") gr::howto::packet_header_default::header_len "

Params: (NONE)"

%feature("docstring") gr::howto::packet_header_default::len_tag_key "

Params: (NONE)"

%feature("docstring") gr::howto::packet_header_default::header_formatter "Encodes the header information in the given tags into bits and places them into .

Uses the following header format: Bits 0-11: The packet length (what was stored in the tag with key ) Bits 12-23: The header number (counts up everytime this function is called) Bit 24-31: 8-Bit CRC All other bits: Are set to zero

If the header length is smaller than 32, bits are simply left out. For this reason, they always start with the LSB.

However, it is recommended to stay above 32 Bits, in order to have a working CRC.

Params: (packet_len, out, tags)"

%feature("docstring") gr::howto::packet_header_default::header_parser "Inverse function to header_formatter().

Reads the bit stream in  and writes a corresponding tag into .

Params: (header, tags)"

%feature("docstring") gr::howto::packet_header_default::make "

Params: (header_len, len_tag_key, num_tag_key, device_id_tag_key, message_type_tag_key, bits_per_byte)"



%feature("docstring") gr::howto::packet_header_ofdm::packet_header_ofdm "

Params: (occupied_carriers, n_syms, len_tag_key, frame_len_tag_key, num_tag_key, device_id_tag_key, message_type_tag_key, bits_per_header_sym, bits_per_payload_sym, header_split, scramble_header)"

%feature("docstring") gr::howto::packet_header_ofdm::~packet_header_ofdm "

Params: (NONE)"

%feature("docstring") gr::howto::packet_header_ofdm::header_formatter "Header formatter.

Does the same as packet_header_default::header_formatter(), but optionally scrambles the bits (this is more important for OFDM to avoid PAPR spikes).

Params: (packet_len, out, tags)"

%feature("docstring") gr::howto::packet_header_ofdm::header_parser "Inverse function to header_formatter().

Does the same as packet_header_default::header_parser(), but adds another tag that stores the number of OFDM symbols in the packet. Note that there is usually no linear connection between the number of OFDM symbols and the packet length because a packet might finish mid-OFDM-symbol.

Params: (header, tags)"

%feature("docstring") gr::howto::packet_header_ofdm::make "

Params: (occupied_carriers, n_syms, len_tag_key, frame_len_tag_key, num_tag_key, device_id_tag_key, message_type_tag_key, bits_per_header_sym, bits_per_payload_sym, header_split, scramble_header)"



%feature("docstring") gr::howto::sc_fdma_carrier_allocator_cvc::len_tag_key "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_carrier_allocator_cvc::fft_len "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_carrier_allocator_cvc::occupied_carriers "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_carrier_allocator_cvc::make "

Params: (fft_len, occupied_carriers, len_tag_key, output_is_shifted)"



%feature("docstring") gr::howto::sc_fdma_equalizer_1d_pilots::sc_fdma_equalizer_1d_pilots "

Params: (fft_len, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, input_is_shifted)"

%feature("docstring") gr::howto::sc_fdma_equalizer_1d_pilots::~sc_fdma_equalizer_1d_pilots "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_equalizer_1d_pilots::reset "Reset the channel information state knowledge.

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_equalizer_1d_pilots::get_channel_state "Return the current channel state.

Params: (taps)"



%feature("docstring") gr::howto::sc_fdma_equalizer_base::sc_fdma_equalizer_base "

Params: (fft_len)"

%feature("docstring") gr::howto::sc_fdma_equalizer_base::~sc_fdma_equalizer_base "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_equalizer_base::reset "Reset the channel information state knowledge.

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_equalizer_base::equalize "Run the actual equalization.

Params: (frame, n_sym, initial_taps, tags)"

%feature("docstring") gr::howto::sc_fdma_equalizer_base::get_channel_state "Return the current channel state.

Params: (taps)"

%feature("docstring") gr::howto::sc_fdma_equalizer_base::fft_len "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_equalizer_base::base "

Params: (NONE)"



%feature("docstring") gr::howto::sc_fdma_equalizer_simpledfe::sc_fdma_equalizer_simpledfe "

Params: (fft_len, constellation, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, alpha, input_is_shifted)"

%feature("docstring") gr::howto::sc_fdma_equalizer_simpledfe::~sc_fdma_equalizer_simpledfe "

Params: (NONE)"

%feature("docstring") gr::howto::sc_fdma_equalizer_simpledfe::equalize "Run the actual equalization.

Params: (frame, n_sym, initial_taps, tags)"

%feature("docstring") gr::howto::sc_fdma_equalizer_simpledfe::make "

Params: (fft_len, constellation, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, alpha, input_is_shifted)"

%feature("docstring") gr::howto::sc_fdma_frame_equalizer_vcvc "sc_fdma frame equalizer

Performs equalization in one or two dimensions on a tagged sc_fdma frame.

This does two things: First, it removes the coarse carrier offset. If a tag is found on the first item with the key 'sc_fdma_sync_carr_offset', this is interpreted as the coarse frequency offset in number of carriers. Next, it performs equalization in one or two dimensions on a tagged sc_fdma frame. The actual equalization is done by a sc_fdma_frame_equalizer object, outside of the block.

Note that the tag with the coarse carrier offset is not removed. Blocks downstream from this block must not attempt to also correct this offset.

Input: a tagged series of sc_fdma symbols. Output: The same as the input, but equalized and frequency-corrected."

%feature("docstring") gr::howto::sc_fdma_frame_equalizer_vcvc::make "

Params: (equalizer, cp_len, len_tag_key, propagate_channel_state, fixed_frame_len)"

%feature("docstring") gr::howto::sc_fdma_interleaver "<+description of block+>"

%feature("docstring") gr::howto::sc_fdma_interleaver::make "Return a shared_ptr to a new instance of howto::sc_fdma_interleaver.

To avoid accidental use of raw pointers, howto::sc_fdma_interleaver's constructor is in a private implementation class. howto::sc_fdma_interleaver::make is the public interface for creating new instances.

Params: (lower_fft_len, upper_fft_len, forward, sync_words, len_tag_key)"

%feature("docstring") gr::howto::sc_fdma_packet_headergenerator_bb "Generates a header for a tagged, streamed packet.

Input: A tagged stream. This is consumed entirely, it is not appended to the output stream. Output: An tagged stream containing the header. The details on the header are set in a header formatter object (of type packet_header_default or a subclass thereof). If only a number of bits is specified, a default header is generated (see packet_header_default)."

%feature("docstring") gr::howto::sc_fdma_packet_headergenerator_bb::make "

Params: (header_formatter, len_tag_key)"

%feature("docstring") gr::howto::sc_fdma_packet_headerparser_b "<+description of block+>"

%feature("docstring") gr::howto::sc_fdma_packet_headerparser_b::make "

Params: (header_formatter)"

%feature("docstring") gr::howto::symbol_decision "<+description of block+>"

%feature("docstring") gr::howto::symbol_decision::make "Return a shared_ptr to a new instance of howto::symbol_decision.

To avoid accidental use of raw pointers, howto::symbol_decision's constructor is in a private implementation class. howto::symbol_decision::make is the public interface for creating new instances.

Params: (fft_len, constellation, len_tag_key)"

%feature("docstring") gr::howto::txt_sink "<+description of block+>"

%feature("docstring") gr::howto::txt_sink::make "Return a shared_ptr to a new instance of howto::txt_sink.

To avoid accidental use of raw pointers, howto::txt_sink's constructor is in a private implementation class. howto::txt_sink::make is the public interface for creating new instances.

Params: (n_data)"

%feature("docstring") gr::howto::user_device_core "<+description of block+>"

%feature("docstring") gr::howto::user_device_core::make "Return a shared_ptr to a new instance of howto::user_device_core.

To avoid accidental use of raw pointers, howto::user_device_core's constructor is in a private implementation class. howto::user_device_core::make is the public interface for creating new instances.

Params: (device_id, packet_len, request_utb, acknowledgement_btu, acknowledgement_utb, acknowledgement_end_btu, acknowledgement_end_utb)"

%feature("docstring") gr::howto::user_device_debug "<+description of block+>"

%feature("docstring") gr::howto::user_device_debug::make "Return a shared_ptr to a new instance of howto::user_device_debug.

To avoid accidental use of raw pointers, howto::user_device_debug's constructor is in a private implementation class. howto::user_device_debug::make is the public interface for creating new instances.

Params: (data, device_id, packet_len, request_utb, acknowledgement_btu, acknowledgement_utb, acknowledgement_end_btu, acknowledgement_end_utb)"