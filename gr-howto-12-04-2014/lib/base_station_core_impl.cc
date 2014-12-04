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
#include "base_station_core_impl.h"
#include "fstream"
using namespace std;

namespace gr {
  namespace howto {

  	enum demux_states_t {
      	STATE_CHECK_MESSAGE_TYPE,       // check message type of incoming data, choose a state
  		STATE_PROCESS_REQUEST,          // check request from user device, send ack to user device
  		STATE_PROCESS_ACK,       		// check ack from user device, prepare for transmitting data
		STATE_DATA_TRANSMISSION,		// transmit data
		STATE_TRANSMISSION_END_ACK,		// send ack for finishing data transmission
    };

    base_station_core::sptr
    base_station_core::make(
    		const std::vector<unsigned char> &data,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb)
    {
      return gnuradio::get_initial_sptr
        (new base_station_core_impl(data, packet_len, request_utb, acknowledgement_btu, acknowledgement_utb,
        		acknowledgement_end_btu, acknowledgement_end_utb));
    }

    /*
     * The private constructor
     */
    base_station_core_impl::base_station_core_impl(
    		const std::vector<unsigned char> &data,
			const unsigned int packet_len,
			const std::vector<unsigned char> &request_utb,
			const std::vector<unsigned char> &acknowledgement_btu,
			const std::vector<unsigned char> &acknowledgement_utb,
			const std::vector<unsigned char> &acknowledgement_end_btu,
			const std::vector<unsigned char> &acknowledgement_end_utb)
      : block("base_station_core",
              io_signature::make(1, 1, sizeof(char)),
              io_signature::make(1, 1, sizeof(char))),
			d_data(data), //for simulation
			d_device_id(12345),
			d_packet_len(packet_len),
			d_request_utb(request_utb),
			d_acknowledgement_btu(acknowledgement_btu),
			d_acknowledgement_utb(acknowledgement_utb),
			d_acknowledgement_end_btu(acknowledgement_end_btu),
			d_acknowledgement_end_utb(acknowledgement_end_utb),
			d_next_tag_pos(0),
			d_consumed_time(0),
			d_resend_for(0),
			d_data_trans_round(0), // for data trans simulation
			d_offset(0),

			//d_state(STATE_CHECK_MESSAGE_TYPE)
			d_state(STATE_DATA_TRANSMISSION) // for debug
    {
    	// initialize the database, register user devices, set idle to be true
    	d_registered_devices.push_back(12345);	d_devices_idle.push_back(true);
    	d_registered_devices.push_back(23456);  d_devices_idle.push_back(true);
    	d_registered_devices.push_back(34567);  d_devices_idle.push_back(true);

    	set_tag_propagation_policy(TPP_DONT);

    	//for simulation
    	d_device_buffer.push_back(12345);
    	d_device_buffer.push_back(23456);
    	d_device_buffer.push_back(34567);
    	set_occupied(12345);
    	set_occupied(23456);
    	set_occupied(34567);
    	d_message_type_buffer.push_back(1);
    	d_message_type_buffer.push_back(1);
    	d_message_type_buffer.push_back(1);
    	d_header_num_buffer.push_back(0);
    	d_header_num_buffer.push_back(0);
    	d_header_num_buffer.push_back(0);

    	int occupied_carriers[48] = {6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 27, 28, 29, 30,
    			31, 33 ,34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58};

    	d_bpsk_points[0]=gr_complex(-1, 0);
    	d_bpsk_points[1]=gr_complex(1, 0);
		d_qpsk_points[0] = gr_complex(-0.707107, -0.707107);
		d_qpsk_points[0] = gr_complex(0.707107, -0.707107);
		d_qpsk_points[0] = gr_complex(-0.707107, 0.707107);
		d_qpsk_points[0] = gr_complex(0.707107, 0.707107);


		std::vector<int> carriers1(20);
		for(int i=0;i<20;i++){
			carriers1[i]=occupied_carriers[i];
		}
		d_carriers_buffer.push_back(carriers1);

		std::vector<int> carriers2(15);
		for(int i=21;i<36;i++){
			carriers2[i-21]=occupied_carriers[i];
		}
		d_carriers_buffer.push_back(carriers2);

		std::vector<int> carriers4(10);
		for(int i=37;i<47;i++){
			carriers4[i-37]=occupied_carriers[i];
		}
		d_carriers_buffer.push_back(carriers4);

		std::vector<int> carriers3(48);
		for(int i=0;i<48;i++){
			carriers3[i]=occupied_carriers[i];
		}
		d_occupied_carriers.push_back(carriers3);

		//data
		long size=13000;
		int offset=0;

		std::vector<unsigned char> data1(sizeof(char)*size);
		for(int i = 0; i < size; i++) {
			data1[i] = d_data[offset++];
			if(offset >= d_data.size()) {
			  offset = 0;
			}
		}
		d_out_buffer.push_back(data1);
		d_data_len_buffer.push_back(size);

		size=15000;
		offset=5;
		std::vector<unsigned char> data2(sizeof(char)*size);
		for(int i = 0; i < size; i++) {
			data2[i] = d_data[offset++];
			if(offset >= d_data.size()) {
			  offset = 0;
			}
		}
		d_out_buffer.push_back(data2);
		d_data_len_buffer.push_back(size);

		size=10000;
		offset=6;
		std::vector<unsigned char> data3(sizeof(char)*size);
		for(int i = 0; i < size; i++) {
			data3[i] = d_data[offset++];
			if(offset >= d_data.size()) {
			  offset = 0;
			}
		}
		d_out_buffer.push_back(data3);
		d_data_len_buffer.push_back(size);

		d_count=0; //3 devices

		//test algorithms
		double a[] = { 1.34, 0.26, 0.96, 1.39, 0.5, 1.38, 0.8, 0.7 };
		double b[] = { 0.52, 0.48, 0.45, 0.61, 0.69, 1.2, 0.58, 0.47 };
		double c[] = { 1.36, 0.56, 0.93, 0.44, 0.81, 0.9, 0.83, 0.18 };
		vector<double> usera(8);
		vector<double> userb(8);
		vector<double> userc(8);
		for (int i = 0; i < 8; i++){
			usera[i] = a[i];
			userb[i] = b[i];
			userc[i] = c[i];
		}

		vector<vector<double> > users;
		users.push_back(usera);
		users.push_back(userb);
		users.push_back(userc);

		//vector<vector<int> > result = maxsum(users);
		//vector<vector<int> > result = maxmin(users);
		vector<vector<int> > result=maxproduct(users);
		std::ofstream outfile2 ("/home/chk/Desktop/subchannel_status.txt");
		for (int i = 0; i < result.size(); i++){

			for(int j = 0; j < result[i].size(); j++){
				outfile2<<result[i][j]<<"   ";
			}
			outfile2 << std::endl;
		}outfile2.close();
    }

    /*
     * Our virtual destructor.
     */
    base_station_core_impl::~base_station_core_impl()
    {
    }

    void
    base_station_core_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    base_station_core_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        unsigned int n_out_per_round = 0; // convenient for data transmission simulation
        std::vector<int> occupied_carriers;
        int message_type = -1;

        int n_available_carriers=0;
        int out_header_size =0;
        int n_out=0;
        // for data trans
        unsigned int size = 0;
		unsigned int offset = d_offset;

		std::vector<tag_t> tags;


		switch (d_state) {
		case STATE_CHECK_MESSAGE_TYPE:
			get_tags_in_range(
				tags, 0,
				nitems_read(0),
				nitems_read(0) + d_packet_len
			);

			message_type = get_message_type(tags);
			if (message_type == 0){					//get request
				consume_each(ninput_items[0]);
				d_state = STATE_PROCESS_REQUEST;
				//fall through

			}else if(message_type==1 && check_ack(in, d_acknowledgement_utb)){				//get ack
				consume_each(ninput_items[0]);
				d_state = STATE_DATA_TRANSMISSION;
				set_occupied(get_device_id(tags));
				break;

			}else if(message_type==2 && check_ack(in, d_acknowledgement_end_utb)){			//get ack data end
				consume_each(ninput_items[0]);
				set_idle(get_device_id(tags));
				d_state = STATE_CHECK_MESSAGE_TYPE;
				d_resend_for=0;
				break;

			}else {

				if(d_resend_for==1 && (clock()-d_time_start)/CLOCKS_PER_SEC >= 5){ // 5 seconds time out, resend ack
					d_state = STATE_PROCESS_REQUEST;
					d_resend_for=0;
				}else if(d_resend_for==2 && (clock()-d_time_start)/CLOCKS_PER_SEC >= 5){ // 5 seconds time out, resend transmission ending ack
					d_state = STATE_TRANSMISSION_END_ACK;
					d_resend_for=0;
				}
				consume_each(ninput_items[0]);
				break;
			}

		case STATE_PROCESS_REQUEST:
			copy_data(d_acknowledgement_btu, out, 0); // message type = 0 (request)
			produce(0, d_acknowledgement_btu.size());

			d_state = STATE_CHECK_MESSAGE_TYPE;
			//d_next_tag_pos = 0;

			d_resend_for = 1;
			d_time_start=clock();
			break;

		case STATE_DATA_TRANSMISSION:


			if(d_device_buffer.size()==0){
				produce(0, 100);
				break;
			}

			if(d_count>=d_device_buffer.size())
				d_count=0;

			occupied_carriers = d_carriers_buffer[d_count];

			n_out_per_round = (30*occupied_carriers.size()-48) * 2 / 8 - 4; // ofdm block 30 symbols; header_len = 48; qpsk has 2 bit/symbol; 8 bit/byte
			if(d_data_len_buffer[d_count]<n_out_per_round){
				n_out_per_round=d_data_len_buffer[d_count];
			}

			for(int i = 0; i < n_out_per_round; i++) {
				out[i] = d_out_buffer[d_count][i];
			}
			d_out_buffer[d_count].erase(d_out_buffer[d_count].begin(),d_out_buffer[d_count].begin()+n_out_per_round);
			d_data_len_buffer[d_count]-=n_out_per_round;



			while(d_next_tag_pos < nitems_written(0) + n_out_per_round) {
				add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_buffer[d_count]));
				add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("message_type"), pmt::from_long(d_message_type_buffer[d_count]));
				add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("header_num"), pmt::from_long(d_header_num_buffer[d_count]));
				add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("occupied_carriers"), pmt::init_s32vector(occupied_carriers.size(),occupied_carriers));
				add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("packet_len"), pmt::from_long(n_out_per_round));
				d_next_tag_pos += n_out_per_round;
			}

			d_header_num_buffer[d_count]++;
			d_count++;

			// check if data transmission completed
			for(int i=0;i<d_device_buffer.size();i++){
				if(d_data_len_buffer[i] <= 0 ){

					d_out_buffer.erase(d_out_buffer.begin()+i);
					d_data_len_buffer.erase(d_data_len_buffer.begin()+i);
					d_device_buffer.erase(d_device_buffer.begin()+i);
					d_message_type_buffer.erase(d_message_type_buffer.begin()+i);
					d_header_num_buffer.erase(d_header_num_buffer.begin()+i);
					d_carriers_buffer.erase(d_carriers_buffer.begin()+i);
					i--;
					//re allocation
					//d_state=STATE_TRANSMISSION_END_ACK;
				}
			}
			produce(0, n_out_per_round);

			break;




			//fall through

		case STATE_TRANSMISSION_END_ACK:
			copy_data(d_acknowledgement_end_btu, out, 2); // message type = 0 (request)
			produce(0, d_acknowledgement_end_btu.size());

			if(d_device_buffer.size()!=0){
				d_state = STATE_DATA_TRANSMISSION;
			}else{
				d_state = STATE_CHECK_MESSAGE_TYPE;
			}

			//d_next_tag_pos = 0;

			d_resend_for = 2;
			d_time_start=clock();
			break;




		default:
			  throw std::runtime_error("invalid state");
		}

        // Tell runtime system how many output items we produced.
        return WORK_CALLED_PRODUCE;
    }

    void
	base_station_core_impl::copy_data(std::vector<unsigned char> &data, unsigned char *out, unsigned int message_type){
		//copy request data
		unsigned int n_out = data.size();
		for(unsigned i = 0; i < n_out; i++) {
		  out[i] = data[i];
		}

		//add tags
		while(d_next_tag_pos < nitems_written(0) + n_out) {
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("device_id"), pmt::from_long(d_device_id));
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("message_type"), pmt::from_long(message_type));
		  add_item_tag(0, d_next_tag_pos, pmt::string_to_symbol("packet_len"), pmt::from_long(d_packet_len));
		  d_next_tag_pos += d_packet_len;
		}
	}

	int
	base_station_core_impl::get_message_type(std::vector<tag_t> &tags)
	{
		if(tags.size()==0){
			return -1;
		}else{
			for (unsigned t = 0; t < tags.size(); t++) {
				if(pmt::equal(pmt::string_to_symbol("message_type"), tags[t].key)){
					return pmt::to_long(tags[t].value);
				}
			}
			return -1;
		}
	}

	int
	base_station_core_impl::get_device_id(std::vector<tag_t> &tags)
	{
		if(tags.size()==0){
			return 0;
		}else{
			for (unsigned t = 0; t < tags.size(); t++) {
				if(pmt::equal(pmt::string_to_symbol("device_id"), tags[t].key)){ //exclude message with wrong device
					return pmt::to_long(tags[t].value);
				}
			}
			return 0;
		}
	}

	bool
	base_station_core_impl::check_ack(const unsigned char *received_ack,std::vector<unsigned char> &ref_ack)
	{
		unsigned i = 0;
		for(i = 0; i<100;i++){ //ack seq is 100 length
			if(received_ack[i]!=ref_ack[i]){
				break;
			}
		}
		if(i!=100)
			return false;
		else
			return true;
	}

	void
	base_station_core_impl::set_occupied(int device_id){
		for(unsigned i=0;i<d_registered_devices.size();i++){
			if(d_registered_devices[i]==device_id)
				d_devices_idle[i]=false;
		}
	}

	void
	base_station_core_impl::set_idle(int device_id){
		for(unsigned i=0;i<d_registered_devices.size();i++){
			if(d_registered_devices[i]==device_id)
				d_devices_idle[i]=true;
		}
	}

	/***********************************************************/
	// this part is for dynamic resource allocation algorithms //
	double base_station_core_impl::find_max(vector<double> a){
		double max_value = -1;
		for (int i = 0; i < a.size(); i++){
			if (a[i] >= max_value){
				max_value = a[i];
			}
		}
		return max_value;
	}
	int base_station_core_impl::find_max_index(double a[]){
		double max_value = 0;
		int max_index = -1;
		int l = sizeof(a);
		for (int i = 0; i < sizeof(a); i++){
			if (a[i] >= max_value){
				max_value = a[i];
				max_index = i;
			}
		}
		return max_index;
	}

	int base_station_core_impl::find_max_index(vector<double> a){
		double max_value = 0;
		int max_index = -1;
		for (int i = 0; i < a.size(); i++){
			if (a[i] >= max_value){
				max_value = a[i];
				max_index = i;
			}
		}
		return max_index;
	}

	int base_station_core_impl::find_min_index(vector<double> a){
		double min_value = 10000;
		int min_index = -1;
		for (int i = 0; i < a.size(); i++){
			if (a[i] <= min_value){
				min_value = a[i];
				min_index = i;
			}
		}
		return min_index;
	}

	// Max-Sum
	vector<vector<int> > base_station_core_impl::maxsum(vector<vector<double> > chan){
		vector<vector<int> > result;
		for (int i = 0; i < chan.size(); i++){
			vector<int> a;
			result.push_back(a);
		}

		double* temp = new double[chan.size()];

		for (int i = 0; i < chan[0].size(); i++){
			for (int j = 0; j < chan.size(); j++){
				temp[j] = chan[j][i];
			}
			result[find_max_index(temp)].push_back(i);
		}
		return result;
	}

	// Max-Min
	vector<vector<int> > base_station_core_impl::maxmin(vector<vector<double> > chan){
		//initialization
		vector<double> R(chan.size(),0);

		vector<vector<int> > result;
		for (int i = 0; i < chan.size(); i++){
			vector<int> a;
			result.push_back(a);
		}

		//step 2
		for (int i = 0; i < chan.size(); i++){
			int n = find_max_index(chan[i]);
			result[i].push_back(n);
			R[i] += chan[i][n];
			for (int j = 0; j < chan.size(); j++){
				chan[j][n] = 0;
			}
		}

		//step3
		while (find_max(chan[0]) != 0){
			int user = find_min_index(R);
			int n = find_max_index(chan[user]);
			result[user].push_back(n);
			R[user] += chan[user][n];
			for (int j = 0; j < chan.size(); j++){
				chan[j][n] = 0;
			}
		}


		return result;
	}

	// Max-Product
	vector<vector<int> > base_station_core_impl::maxproduct(vector<vector<double> > chan){
		//initialization
		double rmin = 0; // assume Rmin is 0 for all users

		vector<double> R(chan.size(), 0);
		vector<vector<double> > nbs_metric;
		vector<double> gain_allocated(chan.size(), 0);
		for (int i = 0; i < chan.size(); i++){
			vector<double> a;
			nbs_metric.push_back(a);
		}

		vector<double> user_set; // should be int
		for (double i = 0; i < chan.size(); i++){
			user_set.push_back(i);
		}

		vector<vector<int> > result;
		for (int i = 0; i < chan.size(); i++){
			vector<int> a;
			result.push_back(a);
		}

		//step 2
		//find user with largest gain
		while (find_max(user_set) >= 0){
			vector<double> temp;

			for (int j = 0; j < user_set.size(); j++){
				if (user_set[j] != -1){
					temp.push_back(find_max(chan[j]));
				}
				else{
					temp.push_back(0);
				}
			}
			int user = find_max_index(temp);

			while (R[user] <= rmin){
				int n = find_max_index(chan[user]);
				result[user].push_back(n);
				R[user] += chan[user][n];
				gain_allocated[user] += chan[user][n];
				for (int m = 0; m < chan.size(); m++){
					chan[m][n] = 0;
				}
				for (int k = 0; k < nbs_metric.size(); k++){
					if (nbs_metric[k].size() != 0){
						nbs_metric[k][n] = 0;
					}
				}
			}
			user_set[user] = -1;

			//calculate nbs metric
			for (int a = 0; a < chan[0].size(); a++){
				nbs_metric[user].push_back(chan[user][a] / gain_allocated[user]);
			}

		}

		//step3
		while (find_max(chan[0]) != 0){
			vector<double> temp;

			for (int j = 0; j < nbs_metric.size(); j++){
				temp.push_back(find_max(nbs_metric[j]));
			}
			int user = find_max_index(temp);

			int n = find_max_index(chan[user]);
			result[user].push_back(n);
			R[user] += chan[user][n];

			//update nbs metric
			gain_allocated[user] += chan[user][n];

			for (int a = 0; a < chan[0].size(); a++){
				nbs_metric[user][a] = chan[user][a] / gain_allocated[user];
			}

			for (int m = 0; m < chan.size(); m++){
				chan[m][n] = 0;
			}
			for (int k = 0; k < nbs_metric.size(); k++){
				nbs_metric[k][n] = 0;
			}

		}


		return result;
	}
























  } /* namespace howto */
} /* namespace gr */

