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

#include <future>


namespace twl
{
	namespace internal
	{
		template<typename Connection_Type, std::size_t recv_timeout>
		class connection
		{
			Connection_Type m_connection;
			mlk::tm::simple_timer m_recv_timer{recv_timeout};
			std::future<void> m_recv_future;

			bool m_recving{false};

		public:
			mlk::slot<const mlk::data_packet&, const mlk::ntw::ip_address&> on_recved;

			template<typename... Connection_Type_Args>
			connection(Connection_Type_Args&&... args) :
				m_connection{std::forward<Connection_Type_Args>(args)...}
			{ }

			template<server_request req>
			void send(const mlk::ntw::ip_address& addr)
			{m_connection.send(request<req>{}(), addr);}

			void recv_threaded()
			{
				if(m_recving)
					return;

				this->recv_start();
				m_recv_future = std::async(std::launch::async,
				[this]
				{
					while(m_recving)
					{
						if(m_recv_timer.timed_out())
						{
							this->recv_end();
							return;
						}

						mlk::ntw::ip_address from;
						auto recved(m_connection.recv(from));
						if(recved.empty())
							continue;

						this->on_recved(recved, from);
						m_recv_timer.restart(); // restart timer
					}
				});
			}

			bool receiving() const noexcept
			{return m_recving;}

		private:
			void recv_start()
			{
				m_recving = true;
				m_recv_timer.run();
			}

			void recv_end()
			{
				m_recving = false;
			}
		};
	}
}


#endif // TWL_NETWORK_CONNECTION_HPP
