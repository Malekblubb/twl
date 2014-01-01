//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_INFO_DECODER_H
#define TWL_NETWORK_INFO_DECODER_H


#include "network_utl.h"
#include "server_base.h"

#include <mlk/containers/container_utl.h>
#include <mlk/tools/type_utl.h>
#include <mlk/types/types.h>


namespace twl
{
	class server_info;

	namespace internal
	{
		inline bool decode_server_info(const basic_server_entry &entry, server_info &info);

		inline bool decode_list_info(const mlk::data_packet& data, ip_list& list)
		{
			if(data.size() < 26) return false;
			mlk::data_packet ip4_spacer{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff};
			mlk::data_packet cmp;

			for(std::size_t i{14}; i < data.size() - 18; i += 18)
			{
				cmp = mlk::data_packet{data.begin() + i, data.begin() + i + 12}; // TODO: 'much' processing, maybe do this better
				auto ip_str(from_binary_ip((cmp == ip4_spacer), mlk::data_packet{data.begin() + i + 12, data.begin() + i + 18 + 12}));
				list.push_back({ip_str, static_cast<int>(data[i + 16] * 0xff + data[i + 16] + data[i + 17])});
			}
			return true;
		}

		inline int decode_count_info(const mlk::data_packet& data)
		{return data.size() > 15 ? (data[14] * 0xff + data[14]) + data[15] : 0;}
	}
}


#endif // TWL_NETWORK_INFO_DECODER_H
