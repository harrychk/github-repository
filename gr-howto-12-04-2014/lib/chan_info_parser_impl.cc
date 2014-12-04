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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "chan_info_parser_impl.h"

#define msg_port_id     pmt::mp("chan_info")

namespace gr {
  namespace howto {

    chan_info_parser::sptr
    chan_info_parser::make(int fft_len)
    {
      return gnuradio::get_initial_sptr
        (new chan_info_parser_impl(fft_len));
    }

    /*
     * The private constructor
     */
    chan_info_parser_impl::chan_info_parser_impl(int fft_len)
      : sync_block("chan_info_parser",
              io_signature::make2(2, 2, sizeof(gr_complex)*fft_len, sizeof(gr_complex)*fft_len),
              io_signature::make(0, 0, 0)),
	d_fft_len(fft_len)
    {
	message_port_register_out(msg_port_id);
        set_output_multiple(2*d_fft_len);
    }

    /*
     * Our virtual destructor.
     */
    chan_info_parser_impl::~chan_info_parser_impl()
    {
    }

    int
    chan_info_parser_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in_chan = (const gr_complex *) input_items[0];
	const gr_complex *in_noise = (const gr_complex *) input_items[1];

	gr_complex chan[d_fft_len];
	gr_complex noise[d_fft_len];
	memcpy((void *) &chan, (void *) in_chan, sizeof(gr_complex)*d_fft_len );
	memcpy((void *) &noise, (void *) in_noise, sizeof(gr_complex)*d_fft_len );

	std::vector<gr_complex> chan_c(d_fft_len);
	std::vector<gr_complex> noise_c(d_fft_len);
	for (int i=0; i<d_fft_len; i++){
	  chan_c[i] = chan[i];
	  noise_c[i] = noise[i];
	}

	//if (noise[0]!=gr_complex(0,0)) {
	  pmt::pmt_t dict(pmt::make_dict());
	  dict = pmt::dict_add(dict, pmt::string_to_symbol("ofdm_sync_chan_taps"), pmt::init_c32vector(d_fft_len, chan_c));
	  dict = pmt::dict_add(dict, pmt::string_to_symbol("ofdm_sync_noise"), pmt::init_c32vector(d_fft_len, noise_c));
	  message_port_pub(msg_port_id, dict);
	//}
        return 2*d_fft_len;
    }

  } /* namespace howto */
} /* namespace gr */

