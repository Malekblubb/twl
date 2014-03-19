//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_MASTER_PARSER_HPP
#define TWL_NETWORK_MASTER_PARSER_HPP


#include "ntw_constants.hpp"
#include "replies.hpp"
#include "utils.hpp"

#include <mlk/network/address.h>


namespace twl
{	
	namespace internal
	{
		class master_parser
		{
			const mlk::data_packet& m_data;
			mlk::data_packet m_workdata;

			masterlist m_listresult;
			int m_countresult;

			bool m_valid{false}, m_countreply{false}, m_listreply{false};

		public:
			master_parser(const mlk::data_packet& data) :
				m_data{data},
				m_countreply{is_reply<server_reply::master_count>(m_data)},
				m_listreply{is_reply<server_reply::master_list>(m_data)}
			{this->parse();}

			bool valid() const noexcept
			{return m_valid;}

			bool countreply() const noexcept
			{return m_countreply;}

			bool listreply() const noexcept
			{return m_listreply;}

			int get_countresult() const noexcept
			{return m_countresult;}

			const masterlist& get_listresult() const noexcept
			{return m_listresult;}

		private:
			void parse()
			{
				if(m_data.size() <= ntw_constants::min_interaction_size())
					return;

				m_workdata = {std::begin(m_data) + 14, std::end(m_data)};

				if(m_countreply)
					this->parse_countinfo();
				else if(m_listreply)
					this->parse_listinfo();
			}

			void parse_countinfo()
			{m_countresult = (m_workdata[0] * 0xff + m_workdata[0]) + m_workdata[1];}

			void parse_listinfo()
			{
				auto ip4_spacer(ntw_constants::ip4_spacer());

				for(std::size_t i{0}; i < m_workdata.size(); i += 18)
				{
					mlk::data_packet cmp{std::begin(m_workdata) + i, std::begin(m_workdata) + i + 12};
					if(cmp != ip4_spacer)
						continue; // dont support ipv6 currently
					m_listresult.emplace_back(from_binary_ip(true, {std::begin(m_workdata) + i + 12, std::begin(m_workdata) + i + 16}),
											  (m_workdata[i + 16] * 0xff + m_workdata[i + 16]) + m_workdata[i + 17], false);
				}
			}
		};
	}
}


#endif // TWL_NETWORK_MASTER_PARSER_HPP
