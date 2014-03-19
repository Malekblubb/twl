//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_UTILS_HPP
#define TWL_NETWORK_UTILS_HPP


#include <mlk/containers/container_utl.h>
#include <mlk/network/address.h>


namespace twl
{
	namespace internal
	{
		inline mlk::data_packet make_connless(const mlk::data_packet& data)
		{
			auto cpy(data);
			mlk::cnt::insert_front(mlk::data_packet{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, cpy);
			return cpy;
		}

		inline mlk::data_packet add_token(unsigned char token, mlk::data_packet& data)
		{
			data.emplace_back(token);
			return data;
		}

		inline std::string from_binary_ip(bool ip4, const mlk::data_packet& data)
		{
			auto buflen(ip4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
			std::vector<char> buf(buflen);

			inet_ntop(ip4 ? AF_INET : AF_INET6, data.data(), buf.data(), buflen);
			return buf.data();
		}
	}
}


#endif // TWL_NETWORK_UTILS_HPP
