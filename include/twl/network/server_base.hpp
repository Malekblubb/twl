//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_BASE_HPP
#define TWL_NETWORK_SERVER_BASE_HPP


#include "connection.hpp"
#include "request_job.hpp"
#include "requests.hpp"


namespace twl
{
	namespace internal
	{
		template<typename Connection_Type, std::size_t timeout>
		class server_base
		{
			internal::connection<Connection_Type, timeout> m_connection;

			std::vector<internal::request_job> m_jobs;

		public:
			bool finished() const noexcept
			{return !m_connection.receiving();}

		protected:
			mlk::slot<const mlk::data_packet&, const mlk::ntw::ip_address&>& on_recved{m_connection.on_recved};

			auto on_job_recv(const mlk::ntw::ip_address& addr)
			{
				auto find(mlk::cnt::find_in_if([&addr](const auto& job){return job.addr() == addr;}, m_jobs));
				if(find == std::end(m_jobs))
					return -1.f;
				find->on_recv();
				auto latency(find->latency());
				m_jobs.erase(find);
				return latency;
			}

			template<server_request req>
			void request(const mlk::ntw::ip_address& addr)
			{
				m_jobs.emplace_back(addr, mlk::tm::time_pnt());
				m_connection.template send<req>(addr);
				this->try_recv();
			}

			void try_recv()
			{
				m_connection.recv_threaded();
			}
		};
	}
}


#endif // TWL_NETWORK_SERVER_BASE_HPP
