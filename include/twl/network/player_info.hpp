//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_PLAYER_INFO_HPP
#define TWL_NETWORK_PLAYER_INFO_HPP


#include <string>
#include <vector>


namespace twl
{
	namespace internal
	{class info_parser;}

	class player_info
	{
		friend class internal::info_parser;

		std::string m_name, m_clan;
		int m_country{-1}, m_score{0};
		bool m_isplayer{false};

		player_info(const std::string& name, const std::string& clan,
					int country, int score, bool isplayer) :
			m_name{name}, m_clan{clan},
			m_country{country}, m_score{score}, m_isplayer{isplayer}
		{ }

	public:
		player_info() = default;

		const std::string& name() const noexcept
		{return m_name;}

		const std::string& clan() const noexcept
		{return m_clan;}

		int country() const noexcept
		{return m_country;}

		int score() const noexcept
		{return m_score;}

		bool is_player() const noexcept
		{return m_isplayer;}
	};

	using player_infos = std::vector<player_info>;
}


#endif // TWL_NETWORK_PLAYER_INFO_HPP
