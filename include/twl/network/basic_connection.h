//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_BASIC_CONNECTION_H
#define TWL_NETWORK_BASIC_CONNECTION_H


#include "server_reply.h"
#include "server_request.h"

#include <mlk/log/log.h>
#include <mlk/network/network.h>
#include <mlk/signals_slots/signals_slots.h>
#include <mlk/time/time.h>
#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		class basic_connection
		{
			static constexpr std::size_t m_max_recv_len{2048};
			mlk::ntw::sock<mlk::ntw::sock_type::udp, false> m_socket;
			mlk::ntw::packet m_req_packet;
			mlk::ntw::ip_address m_from;
			mlk::hrs_time_pnt m_recv_start;

		public:
			mlk::signal m_received;

			basic_connection() = default;
			basic_connection(const mlk::ntw::packet& packet) :
				m_req_packet{packet}
			{ }

			void set_packet(const mlk::ntw::packet& packet)
			{m_req_packet = packet;}

			bool send(const mlk::ntw::ip_address& to)
			{
				m_socket.send(to, m_req_packet.data());
				if(m_socket.error())
				{
					mlk::lerr()["twl::internal::basic_connection::send"] << "counld not send '" << m_req_packet.size() << "' bytes to '" << to << "'";
					return false;
				}
				return true;
			}

			void start_recv()
			{
				mlk::data_packet tmp_data;

				for(;;)
				{
					m_recv_start = mlk::tm::time_pnt();

					while(!timed_out())
					{
						m_from.reset();
						m_socket.recv(m_from, tmp_data, m_max_recv_len);
						if(!m_socket.error())
							mlk::emit_signal(m_received, tmp_data, m_from);
					}

					if(this->timed_out())
						break;
				}
			}

		private:
			bool timed_out() {return mlk::tm::timed_out(m_recv_start, 999);}
		};
	}
}


#endif // TWL_NETWORK_BASIC_CONNECTION_H
