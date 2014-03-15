//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_MASTER_PARSER_HPP
#define TWL_NETWORK_MASTER_PARSER_HPP


#include "ntw_constants.hpp"
#include "replies.hpp"


namespace twl
{
	namespace internal
	{
		class master_parser
		{
			const mlk::data_packet& m_data;
			std::string m_workstr;

			int m_countresult;

			bool m_valid{false}, m_countreply{false}, m_listreply{false};

		public:
			master_parser(const mlk::data_packet& data) :
				m_data{data}
			{this->parse();}

			bool valid() const noexcept
			{return m_valid;}

			bool countreply() const noexcept
			{return m_countreply;}

			bool listreply() const noexcept
			{return m_listreply;}

		private:
			void parse()
			{
				if(m_data.size() <= ntw_constants::min_interaction_size())
					return;

				m_countreply = is_reply<server_reply::master_count>(m_data) ? true : m_listreply = is_reply<server_reply::master_list>(m_data) ? true : false;
				m_workstr = {reinterpret_cast<const char*>(mlk::data_packet{std::begin(m_data) + 14, std::end(m_data)}.data()), m_data.size() - 14};

				if(m_countreply)
					this->parse_countinfo();
				else if(m_listreply)
					this->parse_listinfo();
			}

			void parse_countinfo()
			{m_countresult = (m_workstr[0] * 0xff + m_workstr[0]) + m_workstr[1];}

			void parse_listinfo()
			{

			}
		};
	}
}


#endif // TWL_NETWORK_MASTER_PARSER_HPP
