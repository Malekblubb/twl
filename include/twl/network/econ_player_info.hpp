//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_ECON_PLAYER_INFO_HPP
#define TWL_NETWORK_ECON_PLAYER_INFO_HPP


#include <string>
#include <vector>


namespace twl
{
	namespace internal
	{class econ_parser;}

	class econ_player_info
	{
		friend class internal::econ_parser;

		std::string m_id, m_addr, m_name, m_score;

		econ_player_info(const std::string& id, const std::string& addr, const std::string& name, const std::string& score) :
			m_id{id}, m_addr{addr}, m_name{name}, m_score{score}
		{ }

	public:
		econ_player_info() = default;

		const std::string& id() const noexcept
		{return m_id;}

		const std::string& addr() const noexcept
		{return m_addr;}

		const std::string& name() const noexcept
		{return m_name;}

		const std::string& score() const noexcept
		{return m_score;}
	};

	using econ_player_infos = std::vector<econ_player_info>;
}


#endif // TWL_NETWORK_ECON_PLAYER_INFO_HPP
