//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_GAME_HPP
#define TWL_NETWORK_SERVER_GAME_HPP


#include "info_parser.hpp"
#include "ntw_constants.hpp"
#include "server_base.hpp"
#include "server_game_connection.hpp"


namespace twl
{
	class game_server : public internal::server_base<internal::server_game_connection, internal::ntw_constants::default_timeout()>
	{
		std::vector<server_info> m_infos;

		mlk::ntw::ip_address m_address;
		bool m_addr_set{false};

	public:
		game_server()
		{this->init();}

		game_server(const mlk::ntw::ip_address& addr) :
			m_address{addr},
			m_addr_set{true}
		{this->init();}

		void request_info()
		{
			if(!m_addr_set)
				return;
			this->request_info(m_address);
		}

		void request_info(const mlk::ntw::ip_address& addr)
		{this->request<internal::server_request::game_get_info>(addr);}

		const auto& get_infos() const noexcept
		{return m_infos;}

	private:
		void init()
		{
			this->on_recved =
			[this](const auto& data, const auto& addr)
			{
				auto latency(this->on_job_recv(addr));
				if(latency == -1.f)
					return;

				internal::info_parser ip{data, latency};
				if(ip.valid())
					m_infos.push_back(ip.get_result());
			};
		}
	};
}


#endif // TWL_NETWORK_SERVER_GAME_HPP
