//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_GAME_CONNECTION_HPP
#define TWL_NETWORK_SERVER_GAME_CONNECTION_HPP


#include "ntw_constants.hpp"
#include "utils.hpp"

#include <mlk/network/network.h>
#include <mlk/tools/random_utl.h>


namespace twl
{
	namespace internal
	{
		class server_game_connection
		{
			mlk::ntw::udp_sock<false> m_socket;
			char m_token{mlk::rnd<char>(0, 9)};

		public:
			void send(const mlk::data_packet& data, const mlk::ntw::ip_address& addr)
			{
				auto connless(internal::make_connless(data));
				m_socket.send(addr, internal::add_token(m_token, connless));
			}

			auto recv(mlk::ntw::ip_address& from)
			{
				mlk::data_packet data;
				m_socket.recv(from, data, internal::ntw_constants::max_datasize());
				return data;
			}
		};
	}
}


#endif // TWL_NETWORK_SERVER_GAME_CONNECTION_HPP
