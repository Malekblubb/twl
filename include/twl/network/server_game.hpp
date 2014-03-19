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

		masterlist m_servers;

	public:
		mlk::slot<const server_info&> on_info;

		game_server()
		{this->init();}

		void add_server(const mlk::ntw::ip_address& addr)
		{
			if(!mlk::cnt::exists(addr, m_servers))
				m_servers.push_back(addr);
		}

		void add_masterlist(const masterlist& list)
		{
			m_servers += list;
			mlk::cnt::remove_multiple_but_one(m_servers); // remove double entrys
		}

		void request_info()
		{
			m_infos.clear();
			for(auto& a : m_servers)
				this->request<internal::server_request::game_get_info>(a);
		}

		const server_infos& get_infos() const noexcept
		{return m_infos;}

	private:
		void init()
		{
			this->on_recved =
			[this](const mlk::data_packet& data, const mlk::ntw::ip_address& addr)
			{
				auto latency(this->on_job_recv(addr));
				if(latency == -1.f)
					return;

				internal::info_parser ip{data, addr, latency};
				if(ip.valid())
				{
					auto res(ip.get_result());
					m_infos.push_back(res);
					this->on_info(res);
				}
			};
		}
	};
}


#endif // TWL_NETWORK_SERVER_GAME_HPP
