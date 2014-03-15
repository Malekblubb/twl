//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_UTILS_HPP
#define TWL_NETWORK_UTILS_HPP


#include <mlk/containers/container_utl.h>


namespace twl
{
	namespace internal
	{
		mlk::data_packet make_connless(const mlk::data_packet& data)
		{
			auto cpy(data);
			mlk::cnt::insert_front(mlk::data_packet{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, cpy);
			return cpy;
		}

		mlk::data_packet add_token(unsigned char token, mlk::data_packet& data)
		{
			data.emplace_back(token);
			return data;
		}
	}
}


#endif // TWL_NETWORK_UTILS_HPP
