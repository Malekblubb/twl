//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_REQUEST_JOB_HPP
#define TWL_NETWORK_REQUEST_JOB_HPP


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

		public:
			request_job(const mlk::ntw::ip_address& addr, const mlk::hrs_time_pnt& send_tp) :
				m_address{addr},
				m_send_tp{send_tp}
			{ }

			const auto& addr() const noexcept
			{return m_address;}

			auto latency() const noexcept
			{return mlk::tm::duration_as<float>(m_send_tp, m_recv_tp);}

			void on_recv() noexcept
			{m_recv_tp = mlk::tm::time_pnt();}
		};
	}
}


#endif // TWL_NETWORK_REQUEST_JOB_HPP
