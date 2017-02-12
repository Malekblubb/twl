//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_ECON_PARSER_HPP
#define TWL_NETWORK_ECON_PARSER_HPP

#include "econ_player_info.hpp"

#include <mlk/tools/stl_string_utl.h>
#include <mlk/types/types.h>

namespace twl
{
	namespace internal
	{
		class econ_parser
		{
			std::string m_workstr;

			econ_player_infos m_status_result;

			bool m_conn_successful_reply{false}, m_status_reply{false};

		public:
			econ_parser(const mlk::data_packet& data)
				: m_workstr{std::begin(data), std::end(data)}
			{
				this->parse();
			}

			bool login_reply() const noexcept
			{
				return m_conn_successful_reply;
			}

			bool status_reply() const noexcept { return m_status_reply; }

			const econ_player_infos& get_status_reply() const noexcept
			{
				return m_status_result;
			}

		private:
			void parse()
			{
				this->get_reply_type();
				if(m_status_reply) this->parse_status_reply();
			}

			void get_reply_type()
			{
				m_conn_successful_reply = mlk::stl_string::contains(
					"Authentication successful. External console access "
					"granted.",
					m_workstr);
				m_status_reply =
					mlk::stl_string::contains("id=", m_workstr) &&
					mlk::stl_string::contains("addr=", m_workstr) &&
					mlk::stl_string::contains("name=", m_workstr) &&
					mlk::stl_string::contains("id=", m_workstr) &&
					!mlk::stl_string::contains("cid", m_workstr);
			}

			void parse_status_reply()
			{
				auto cpy(m_workstr);
				auto num_players(mlk::stl_string::count_of('\n', cpy));

				for(std::size_t i{0}; i < num_players; ++i) {
					auto id_pos(cpy.find("id="));
					auto addr_pos(cpy.find("addr="));
					auto name_pos(cpy.find("name="));
					auto score_pos(cpy.find("score="));
					auto linebreak(cpy.find('\n'));

					m_status_result.emplace_back(econ_player_info{
						cpy.substr(id_pos + 3, addr_pos - id_pos - 4),
						cpy.substr(addr_pos + 5, name_pos - addr_pos - 6),
						cpy.substr(name_pos + 6, score_pos - name_pos - 8),
						cpy.substr(score_pos + 6, linebreak - score_pos - 8)});

					cpy.erase(0, linebreak + 1);
				}
			}
		};
	}
}

#endif// TWL_NETWORK_ECON_PARSER_HPP
