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

#ifndef INCLUDED_HOWTO_OFDM_FRAME_EQUALIZER_VCVC_IMPL_H
#define INCLUDED_HOWTO_OFDM_FRAME_EQUALIZER_VCVC_IMPL_H

#include <howto/ofdm_frame_equalizer_vcvc.h>
#include <boost/crc.hpp>

namespace gr {
  namespace howto {

    class ofdm_frame_equalizer_vcvc_impl : public ofdm_frame_equalizer_vcvc
    {
     private:
      int d_fft_len;
      int d_cp_len;
      gr::howto::constellation_sptr d_constellation;
      unsigned d_device_id;
      std::vector<int> d_occupied_carriers_total;
      std::vector<std::vector<int> > d_pilot_carriers;
      std::vector<std::vector<gr_complex> > d_pilot_symbols;
      gr::howto::ofdm_equalizer_base::sptr d_eq;
      bool d_propagate_channel_state;
      const int d_fixed_frame_len;
      std::vector<gr_complex> d_channel_state;

      boost::crc_optimal<8, 0x07, 0xFF, 0x00, false, false>  d_crc_impl;

      void get_occupied_carriers_buffer(std::vector<std::vector<int> > &buffer, std::vector<int> &total);
      int header_parser(std::vector<unsigned char> &in,std::vector<tag_t> &tags);

     protected:
      void parse_length_tags(
	  const std::vector<std::vector<tag_t> > &tags,
	  gr_vector_int &n_input_items_reqd
      );

     public:
      ofdm_frame_equalizer_vcvc_impl(
	  int fft_len,
	  unsigned device_id,
	  //const gr::howto::constellation_sptr &constellation,
	  const std::vector<std::vector<int> > &pilot_carriers,
	  const std::vector<std::vector<gr_complex> > &pilot_symbols,
	  //gr::howto::ofdm_equalizer_base::sptr equalizer,
	  int cp_len,
	  const std::string &len_tag_key,
	  bool propagate_channel_state,
	  int fixed_frame_len
      );
      ~ofdm_frame_equalizer_vcvc_impl();

      int work(int noutput_items,
	  gr_vector_int &ninput_items,
	  gr_vector_const_void_star &input_items,
	  gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_OFDM_FRAME_EQUALIZER_VCVC_IMPL_H */

