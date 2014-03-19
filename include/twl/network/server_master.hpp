//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_MASTER_HPP
#define TWL_NETWORK_SERVER_MASTER_HPP


#include "master_parser.hpp"
#include "ntw_constants.hpp"
#include "server_base.hpp"
#include "server_master_connection.hpp"


namespace twl
{
	class master_server : public internal::server_base<internal::server_master_connection, internal::ntw_constants::default_timeout()>
	{
		std::vector<mlk::ntw::ip_address> m_servers;

		masterlist m_listresult;
		int m_countresult{0};

	public:
		mlk::slot<int> on_count;
		mlk::slot<const masterlist&> on_list;

		master_server()
		{this->init();}

		void add_master(const mlk::ntw::ip_address& addr)
		{
			if(mlk::cnt::exists(addr, m_servers))
				return;
			m_servers.push_back(addr);
		}

		void request_count()
		{
			m_countresult = 0;
			for(auto& a : m_servers)
				this->request<internal::server_request::master_get_count>(a);
		}

		void request_list()
		{
			m_listresult.clear();
			for(auto& a : m_servers)
				this->request<internal::server_request::master_get_list>(a);
		}

		int get_count() const noexcept
		{return m_countresult;}

		const auto& get_list() const noexcept
		{return m_listresult;}

	private:
		void init()
		{
			this->on_recved =
			[this](const auto& data, const auto&)
			{
				internal::master_parser mp{data};
				if(mp.countreply())
				{
					auto count(mp.get_countresult());
					m_countresult += count;
					this->on_count(count);
				}
				else if(mp.listreply())
				{
					auto list(mp.get_listresult());
					m_listresult += list;
					this->on_list(list);
				}
			};
		}
	};
}


#endif // TWL_NETWORK_SERVER_MASTER_HPP
