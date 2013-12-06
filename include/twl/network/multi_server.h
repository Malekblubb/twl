//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_MULTI_SERVER_H
#define TWL_NETWORK_MULTI_SERVER_H


#include "server_base.h"
#include "server_info.h"
#include "server_request.h"

#include <mlk/tools/random_utl.h>


namespace twl
{
	class multi_server : public internal::server_base
	{
		using info_vec = std::vector<server_info>;

		unsigned char m_token{mlk::rnd<unsigned char>(0, 9)}; // get random token
		info_vec m_infos;

	public:
		multi_server() :
			internal::server_base{mlk::ntw::packet{internal::server_req<internal::req_type::info>{}.request_data()}.add({m_token})}
		{ }

		~multi_server() = default;

		void add(const ip_list& list)
		{m_servers.insert(m_servers.end(), list.begin(), list.end());}

		const info_vec& get_info() noexcept
		{
			this->refresh();
			return m_infos;
		}

	private:
		void make_entry(const internal::basic_server_entry& entry) override
		{m_infos.push_back(internal::make_info(entry));}
	};
}


#endif // TWL_NETWORK_MULTI_SERVER_H
