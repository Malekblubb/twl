//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_BASE_H
#define TWL_NETWORK_SERVER_BASE_H


#include "basic_connection.h"

#include <future>


namespace twl
{
	namespace internal
	{
		class server_base
		{
			basic_connection m_connection;
			std::vector<mlk::ntw::ip_address> m_servers; // added servers
			mlk::slot<void(mlk::data_packet&)> m_on_recv;

		public:
			server_base(const mlk::ntw::packet& packet) :
				m_connection{packet}
			{
				m_on_recv += [this](const mlk::data_packet& data){this->make_entry(data);};
				mlk::link_signal(m_connection.m_received, m_on_recv);
			}

			void add(const mlk::ntw::ip_address& server_address)
			{m_servers.push_back(server_address);}

		protected:
			void send_reuest()
			{
				for(auto& a : m_servers)
					if(!m_connection.send(a))
						return;

				std::async(std::launch::async,
				[this]
				{
					m_connection.recv();
				});
			}

		private:
			virtual void make_entry(const mlk::data_packet& data) = 0;
		};
	}
}


#endif // TWL_NETWORK_SERVER_BASE_H
