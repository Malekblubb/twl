//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_BASIC_SERVER_ENTRY_H
#define TWL_NETWORK_BASIC_SERVER_ENTRY_H


#include <mlk/network/network.h>
#include <mlk/time/time.h>
#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		// is used by server_base
		// this type just holds the send and recv time points, address and data
		// and calculates the ping
		class basic_server_entry
		{
			mlk::data_packet m_data;
			mlk::ntw::ip_address m_address;
			mlk::hrs_time_pnt m_send_pnt;
			mlk::hrs_time_pnt m_recv_pnt;

		public:
			basic_server_entry() = default;

			basic_server_entry(const mlk::ntw::ip_address& address) :
				m_address{address}
			{ }

			void on_send() noexcept
			{m_send_pnt = mlk::tm::time_pnt();}

			void on_recv() noexcept
			{m_recv_pnt = mlk::tm::time_pnt();}

			auto ping() const noexcept -> decltype(mlk::tm::duration_as<float>(m_send_pnt, m_recv_pnt))
			{return mlk::tm::duration_as<float>(m_send_pnt, m_recv_pnt);}

			auto address() const noexcept -> decltype((m_address))
			{return m_address;}

			mlk::data_packet& data() noexcept
			{return m_data;}

			const mlk::data_packet& data() const noexcept
			{return m_data;}
		};
	}
}


#endif // TWL_NETWORK_BASIC_SERVER_ENTRY_H
