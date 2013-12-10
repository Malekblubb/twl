//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_INFO_H
#define TWL_NETWORK_SERVER_INFO_H


#include "client_info.h"
#include "info_decoder.h"

#include <string>
#include <vector>


namespace twl
{
	using server_infos = std::vector<server_info>;

	struct server_info
	{
		std::string name;
		std::string game_type;
		std::string map_name;
		std::string version;
		int max_clients{0};
		int num_clients{0};
		int max_players{0};
		int num_players{0};
		float ping;
		std::vector<client_info> clients;

		bool m_empty{true};
		bool is_valid() const noexcept
		{return !m_empty;}
	};

	namespace internal
	{
		server_info make_info(const basic_server_entry& entry)
		{
			server_info tmp;
			decode_server_info(entry, tmp);
			tmp.ping = entry.ping(); // no 'decoding' stuff
			tmp.m_empty = false;
			return tmp;
		}
	}
}


#endif // TWL_NETWORK_SERVER_INFO_H
