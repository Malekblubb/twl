//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_INFO_DECODER_H
#define TWL_NETWORK_INFO_DECODER_H


#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		enum class decode_type : int {server_info, mstr_list_info, m_str_count_info};

		template<decode_type type>
		bool decode_as(const mlk::data_packet&);

		template<>
		bool decode_as<decode_type::server_info>(const mlk::data_packet& data)
		{

		}
	}
}


#endif // TWL_NETWORK_INFO_DECODER_H
