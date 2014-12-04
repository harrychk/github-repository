/* -*- c++ -*- */
/* Copyright 2012 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#include <howto/packet_header_default.h>

namespace gr {
  namespace howto {

    packet_header_default::sptr
    packet_header_default::make(
		    long header_len,
		    const std::string &len_tag_key,
		    const std::string &num_tag_key,
			const std::string &device_id_tag_key,
			const std::string &message_type_tag_key,
		    int bits_per_byte)
    {
      return packet_header_default::sptr(new packet_header_default(header_len, len_tag_key, num_tag_key,
    		  device_id_tag_key, message_type_tag_key, bits_per_byte)); //chk
    }

    const unsigned MASK_LUT[9] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x2F, 0x7F, 0xFF};
    packet_header_default::packet_header_default(
		    long header_len,
		    const std::string &len_tag_key,
		    const std::string &num_tag_key,
			const std::string &device_id_tag_key,
			const std::string &message_type_tag_key,
		    int bits_per_byte)
      : d_header_len(header_len),
      d_len_tag_key(pmt::string_to_symbol(len_tag_key)),
      d_num_tag_key(num_tag_key.empty() ? pmt::PMT_NIL : pmt::string_to_symbol(num_tag_key)),
	  d_device_id_tag_key(pmt::string_to_symbol(device_id_tag_key)), //chk
	  d_message_type_tag_key(pmt::string_to_symbol(message_type_tag_key)), //chk
      d_bits_per_byte(bits_per_byte),
      d_header_number(0)
    {
      if (d_bits_per_byte < 1 || d_bits_per_byte > 8) {
	throw std::invalid_argument("bits_per_byte must be in [1, 8]");
      }
      d_mask = MASK_LUT[d_bits_per_byte];
    }

    packet_header_default::~packet_header_default()
    {
    }

    bool packet_header_default::header_formatter(
    		long packet_len,
			unsigned char *out,
			const std::vector<tag_t> &tags
    )
    {
    	long device_id = 0;
    	long message_type = 4;
    	//long header_num=0;
    	for (int i = 0; i<tags.size(); i++){
    		if(pmt::equal(tags[i].key, pmt::string_to_symbol("device_id"))){
    			device_id=pmt::to_long(tags[i].value);
    		}
    		if(pmt::equal(tags[i].key, pmt::string_to_symbol("message_type"))){
				message_type=pmt::to_long(tags[i].value);
			}
    		if(pmt::equal(tags[i].key, pmt::string_to_symbol("header_num"))){
    			d_header_number=pmt::to_long(tags[i].value);
			}
    	}

      device_id &= 0xFFFF;
      packet_len &= 0x0FFF;
      d_crc_impl.reset();
      d_crc_impl.process_bytes((void const *) &device_id, 2); // chk
      d_crc_impl.process_bytes((void const *) &packet_len, 2);
      d_crc_impl.process_bytes((void const *) &d_header_number, 2);
      unsigned char crc = d_crc_impl();

      memset(out, 0x00, d_header_len);
      int k = 0; // Position in out
      for (int i = 0; i < 16 && k < d_header_len; i += d_bits_per_byte, k++) { // chk
    	  out[k] = (unsigned char) ((device_id >> i) & d_mask);
      }
      for (int i = 0; i < 2 && k < d_header_len; i += d_bits_per_byte, k++) { // chk
      	out[k] = (unsigned char) ((message_type >> i) & d_mask);
            }
      for (int i = 0; i < 11 && k < d_header_len; i += d_bits_per_byte, k++) {
    	  out[k] = (unsigned char) ((packet_len >> i) & d_mask);
      }
      for (int i = 0; i < 11 && k < d_header_len; i += d_bits_per_byte, k++) {
    	  out[k] = (unsigned char) ((d_header_number >> i) & d_mask);
      }
      for (int i = 0; i < 8 && k < d_header_len; i += d_bits_per_byte, k++) {
    	  out[k] = (unsigned char) ((crc >> i) & d_mask);
      }
      d_header_number++;
      d_header_number &= 0x0FFF;

      return true;
    }

    bool packet_header_default::header_parser(
	const unsigned char *in,
	std::vector<tag_t> &tags)
    {
      unsigned header_len = 0;
      unsigned header_num = 0;
      unsigned device_id = 0;
      unsigned message_type = 0;
      tag_t tag;

      int k = 0; // Position in "in"
      for (int i = 0; i < 16 && k < d_header_len; i += d_bits_per_byte, k++) {
    	  device_id |= (((int) in[k]) & d_mask) << i;
      }
      tag.key = d_device_id_tag_key;
      tag.value = pmt::from_long(device_id);
      tags.push_back(tag);
      if (k >= d_header_len) {
    	  return true;
      }

      for (int i = 0; i < 2 && k < d_header_len; i += d_bits_per_byte, k++) {
		  message_type |= (((int) in[k]) & d_mask) << i;
	  }
	  tag.key = d_message_type_tag_key;
	  tag.value = pmt::from_long(message_type);
	  tags.push_back(tag);
	  if (k >= d_header_len) {
		  return true;
	  }

      for (int i = 0; i < 11 && k < d_header_len; i += d_bits_per_byte, k++) {
    	  header_len |= (((int) in[k]) & d_mask) << i;
      }
      tag.key = d_len_tag_key;
      tag.value = pmt::from_long(header_len);
      tags.push_back(tag);
      if (k >= d_header_len) {
    	  return true;
      }
      if (d_num_tag_key == pmt::PMT_NIL) {
    	  k += 11;
      } else {
	for (int i = 0; i < 11 && k < d_header_len; i += d_bits_per_byte, k++) {
	  header_num |= (((int) in[k]) & d_mask) << i;
	}
	tag.key = d_num_tag_key;
	tag.value = pmt::from_long(header_num);
	tags.push_back(tag);
      }
      if (k >= d_header_len) {
	return true;
      }

      d_crc_impl.reset();
      d_crc_impl.process_bytes((void const *) &device_id, 2); // chk
      d_crc_impl.process_bytes((void const *) &header_len, 2);
      d_crc_impl.process_bytes((void const *) &header_num, 2);
      unsigned char crc_calcd = d_crc_impl();
      for (int i = 0; i < 8 && k < d_header_len; i += d_bits_per_byte, k++) {
	  if ( (((int) in[k]) & d_mask) != (((int) crc_calcd >> i) & d_mask) ) {
	    return false;
	  }
      }

      return true;
    }

  } /* namespace howto */
} /* namespace gr */

