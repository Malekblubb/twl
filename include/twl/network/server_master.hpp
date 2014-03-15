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

	public:
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
			for(auto& a : m_servers)
				this->request<internal::server_request::master_get_count>(a);
		}

		void request_list()
		{

		}

	private:
		void init()
		{
			this->on_recved =
			[](const auto& data, const auto& addr)
			{
				internal::master_parser mp{data};
				std::cout << "recved: " << data.data() << std::endl;
			};
		}
	};
}


#endif // TWL_NETWORK_SERVER_MASTER_HPP
