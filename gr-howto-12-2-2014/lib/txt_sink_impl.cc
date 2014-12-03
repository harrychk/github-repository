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
#include "txt_sink_impl.h"
#include "fstream"

namespace gr {
  namespace howto {

    txt_sink::sptr
    txt_sink::make(int n_data)
    {
      return gnuradio::get_initial_sptr
        (new txt_sink_impl(n_data));
    }

    /*
     * The private constructor
     */
    txt_sink_impl::txt_sink_impl(int n_data)
      : sync_block("txt_sink",
              io_signature::make(1, 1, sizeof(char)),
              io_signature::make(0, 0, 0)),
	d_n_data(n_data)
    {}

    /*
     * Our virtual destructor.
     */
    txt_sink_impl::~txt_sink_impl()
    {
    }

    

    int
    txt_sink_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
	//const gr_complex *in2 = (const gr_complex *) input_items[1];
	
	//std::vector<gr_complex*> est(d_n_data);
	gr_complex est[d_n_data];
	//gr_complex *out=(gr_complex *) &est;
	//for (int i=0;i<d_n_data;i++){
	//  est[i]=*in;
	//  in++;
	//}
	memcpy((void *) &est, (void *) in, sizeof(gr_complex)*d_n_data );
	//gr_complex noise_c;
	//memcpy((void *) &noise_c, (void *) in2, sizeof(gr_complex) );
	//if (est[10]!=gr_complex(0,0)){
	  //std::ofstream outfile ("/home/chk/Desktop/check_output.txt");
	  std::ofstream ofs;
	  ofs.open ("/home/chk/Desktop/check_output.txt",std::ofstream::app);
          for (int i=0;i<d_n_data;i++){
        	  ofs<<est[i]<<"\n";
	  
	  }
	  //for (int i=0;i<d_n_data;i++){
	  //  outfile<<noise_c<<"\n";
	  
	  //}
	  //outfile.close();
          ofs.close();
	//}
        return 1;
    }

  } /* namespace howto */
} /* namespace gr */

