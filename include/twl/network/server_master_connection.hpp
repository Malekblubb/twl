//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_MASTER_CONNECTION_HPP
#define TWL_NETWORK_SERVER_MASTER_CONNECTION_HPP


#include "ntw_constants.hpp"
#include "utils.hpp"

#include <mlk/network/network.h>


namespace twl
{
	namespace internal
	{
		class server_master_connection
		{
			mlk::ntw::udp_sock<false> m_socket;

		public:
			void send(const mlk::data_packet& data, const mlk::ntw::ip_address& addr)
			{
				m_socket.send(addr, internal::make_connless(data));
			}

			auto recv(mlk::ntw::ip_address& from)
			{
				mlk::data_packet data(internal::ntw_constants::max_datasize());
				m_socket.recv(from, data, internal::ntw_constants::max_datasize());
				return data;
			}
		};
	}
}



#endif // TWL_NETWORK_SERVER_MASTER_CONNECTION_HPP
