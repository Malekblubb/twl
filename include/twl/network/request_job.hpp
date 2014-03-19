//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_REQUEST_JOB_HPP
#define TWL_NETWORK_REQUEST_JOB_HPP


#include "requests.hpp"

#include <mlk/network/address.h>
#include <mlk/time/time_utl.h>
#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		class request_job
		{
			mlk::ntw::ip_address m_address;
			mlk::hrs_time_pnt m_send_tp;
			mlk::hrs_time_pnt m_recv_tp;
			std::size_t m_timeout;
			mlk::ushort m_max_resend, m_current_resend{0};
			server_request m_request;

			bool m_need_resend{true}, m_need_delete{false}, m_sent{false};

		public:
			request_job() = default;

			request_job(const mlk::ntw::ip_address& addr, std::size_t timeout, mlk::ushort max_resend, server_request req) :
				m_address{addr},
				m_timeout{timeout},
				m_max_resend{max_resend},
				m_request{req}
			{ }

			void update()
			{
				if(m_need_delete)
					return;

				if(m_sent && mlk::tm::timed_out(m_send_tp, m_timeout))
				{
					m_need_resend = true;
					++m_current_resend;
					if(m_current_resend >= m_max_resend)
						m_need_delete = true;
				}
			}

			void on_resend() noexcept
			{
				m_send_tp = mlk::tm::time_pnt();
				m_need_resend = false;
				m_sent = true;
			}

			void on_recv() noexcept
			{m_recv_tp = mlk::tm::time_pnt();}


			const mlk::ntw::ip_address& addr() const noexcept
			{return m_address;}

			float latency() const noexcept
			{return mlk::tm::duration_as<float>(m_send_tp, m_recv_tp);}

			bool need_resend() const noexcept
			{return m_need_resend;}

			bool need_delete() const noexcept
			{return m_need_delete;}

			server_request request_type() const noexcept
			{return m_request;}
		};
	}
}


#endif // TWL_NETWORK_REQUEST_JOB_HPP
