//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_CONNECTION_HPP
#define TWL_NETWORK_CONNECTION_HPP


#include "requests.hpp"

#include <mlk/network/network.h>
#include <mlk/signals_slots/slot.h>
#include <mlk/time/simple_timer.h>


namespace twl
{
	namespace internal
	{
		template<typename Connection_Type>
		class connection
		{
			Connection_Type m_connection;

		public:
			mlk::slot<const mlk::data_packet&, const mlk::ntw::ip_address&> on_recved;

			template<typename... Connection_Type_Args>
			connection(Connection_Type_Args&&... args) :
				m_connection{std::forward<Connection_Type_Args>(args)...}
			{ }

			template<server_request req>
			void send(const mlk::ntw::ip_address& addr)
			{m_connection.send(request<req>{}(), addr);}

			void send(const mlk::ntw::ip_address &addr, const mlk::data_packet& data)
			{m_connection.send(data, addr);}

			void recv()
			{
				mlk::ntw::ip_address from;
				auto recved(m_connection.recv(from));
				if(!recved.empty())
					this->on_recved(recved, from);
			}
		};
	}
}


#endif // TWL_NETWORK_CONNECTION_HPP
