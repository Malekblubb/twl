//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_INFO_HPP
#define TWL_NETWORK_SERVER_INFO_HPP

#include "player_info.hpp"

#include <mlk/network/network_utl.h>

#include <string>
#include <vector>

namespace twl
{
	namespace internal
	{
		class info_parser;
	}

	class server_info
	{
		friend class internal::info_parser;

		mlk::ntw::ip_address m_address;
		std::string m_version, m_name, m_mapname, m_gametype;
		int m_flags{0}, m_numplayers{0}, m_maxplayers{0}, m_numclients{0},
			m_maxclients{0};
		float m_latency{0.f};
		player_infos m_players;

		server_info(const mlk::ntw::ip_address& addr,
					const std::string& version, const std::string& name,
					const std::string& mapname, const std::string& gametype,
					int flags, int numplayers, int maxplayers, int numclients,
					int maxclients, float latency)
			: m_address{addr},
			  m_version{version},
			  m_name{name},
			  m_mapname{mapname},
			  m_gametype{gametype},
			  m_flags{flags},
			  m_numplayers{numplayers},
			  m_maxplayers{maxplayers},
			  m_numclients{numclients},
			  m_maxclients{maxclients},
			  m_latency{latency}
		{
		}

		void add_player(player_info&& pi) { m_players.emplace_back(pi); }

	public:
		server_info() = default;

		const mlk::ntw::ip_address& address() const noexcept
		{
			return m_address;
		}

		const std::string& version() const noexcept { return m_version; }

		const std::string& name() const noexcept { return m_name; }

		const std::string& mapname() const noexcept { return m_mapname; }

		const std::string& gametype() const noexcept { return m_gametype; }

		int flags() const noexcept { return m_flags; }

		int numplayers() const noexcept { return m_numplayers; }

		int maxplayers() const noexcept { return m_maxplayers; }

		int numclients() const noexcept { return m_numclients; }

		int maxclients() const noexcept { return m_maxclients; }

		const player_infos& players() const noexcept { return m_players; }

		float ping() const noexcept { return m_latency; }
	};

	using server_infos = std::vector<server_info>;
}

#endif// TWL_NETWORK_SERVER_INFO_HPP
