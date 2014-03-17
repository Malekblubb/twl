//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_BASE_HPP
#define TWL_NETWORK_SERVER_BASE_HPP


#include "connection.hpp"
#include "ntw_constants.hpp"
#include "request_job.hpp"
#include "requests.hpp"

#include <mlk/containers/container_utl.h>
#include <mlk/signals_slots/slot.h>


namespace twl
{
	namespace internal
	{
		template<typename Connection_Type, std::size_t timeout>
		class server_base
		{
			internal::connection<Connection_Type, timeout> m_connection;

			std::vector<internal::request_job> m_jobs;
			std::size_t m_running_jobs{0};

			bool m_running{false};

		public:
			mlk::slot<> on_finish;

			void update()
			{
				m_connection.recv();

				// update jobs
				for(auto& job : m_jobs)
				{
					job.update();

					if(m_running_jobs < internal::ntw_constants::max_concurrent_requests())
					{
						if(job.need_resend())
						{
							m_connection.send(job.addr(), get_request(job.request_type())());
							job.on_resend();

							++m_running_jobs;
						}
					}

					if(job.need_delete())
						--m_running_jobs;
				}

				// remove jobs that are timed out
				mlk::cnt::remove_all_if([](const auto& job){return job.need_delete();}, m_jobs);

				if(m_running && m_jobs.empty())
				{
					m_running = false;
					this->on_finish();
				}
			}

			bool finished() const noexcept
			{return !m_connection.receiving();}

		protected:
			mlk::slot<const mlk::data_packet&, const mlk::ntw::ip_address&>& on_recved{m_connection.on_recved};

			auto on_job_recv(const mlk::ntw::ip_address& addr)
			{
				auto job(mlk::cnt::find_in_if([&addr](const auto& job){return job.addr() == addr;}, m_jobs));
				if(job == std::end(m_jobs))
					return -1.f;
				job->on_recv();
				auto latency(job->latency());
				m_jobs.erase(job);

				--m_running_jobs;

				return latency;
			}

			template<server_request req>
			void request(const mlk::ntw::ip_address& addr)
			{
				m_running = true;

				if(!mlk::cnt::exists_if(
							[&addr](const auto& job){return (job.addr() == addr) && job.request_type() == req;}, m_jobs))
					m_jobs.emplace_back(addr, timeout, internal::ntw_constants::resend_timeouts(), req);
			}
		};
	}
}


#endif // TWL_NETWORK_SERVER_BASE_HPP
