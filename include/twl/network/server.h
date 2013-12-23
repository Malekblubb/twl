//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_H
#define TWL_NETWORK_SERVER_H


#include "server_base.h"
#include "server_info.h"


#include <mlk/tools/random_utl.h>


namespace twl
{
	class server : public internal::server_base
	{
		server_info m_info;

	public:
		server(const mlk::ntw::ip_address& address) :
			internal::server_base{mlk::ntw::packet{
								  internal::server_req<internal::req_type::info>{}.request_data()}.append(mlk::data_packet{mlk::rnd<unsigned char>(0, 9)})}
		{this->set_address(address);}

		void add(const mlk::ntw::ip_address &address) = delete;
		void set_address(const mlk::ntw::ip_address& address)
		{m_servers.clear(); m_servers.push_back(address);}

		const server_info& get_info() noexcept
		{
			this->refresh();
			return m_info;
		}

	private:
		void make_entry(const internal::basic_server_entry &entry)
		{m_info = internal::make_info(entry);}
	};
}



#endif // TWL_NETWORK_SERVER_H
