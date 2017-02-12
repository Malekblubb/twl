//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_INFO_PARSER_HPP
#define TWL_NETWORK_INFO_PARSER_HPP

#include "ntw_constants.hpp"
#include "server_info.hpp"

#include <mlk/containers/container_utl.h>

namespace twl
{
	namespace internal
	{
		class info_parser
		{
			const mlk::data_packet& m_data;
			mlk::ntw::ip_address m_from;
			float m_latency;
			std::string m_workstr;

			server_info m_result;

			bool m_valid{false};

		public:
			info_parser(const mlk::data_packet& data,
						const mlk::ntw::ip_address& from, float latency)
				: m_data{data}, m_from{from}, m_latency{latency}
			{
				this->parse();
			}

			const server_info& get_result() const noexcept { return m_result; }

			bool valid() const noexcept { return m_valid; }

		private:
			void parse()
			{
				if(m_data.size() <= ntw_constants::min_interaction_size())
					return;

				m_workstr = {reinterpret_cast<const char*>(mlk::data_packet{
								 std::begin(m_data) + 17,
								 std::end(m_data)}.data()),
							 m_data.size() - 17};

				m_result = {m_from,
							this->get_next<std::string>(),
							this->get_next<std::string>(),
							this->get_next<std::string>(),
							this->get_next<std::string>(),
							this->get_next<int>(),
							this->get_next<int>(),
							this->get_next<int>(),
							this->get_next<int>(),
							this->get_next<int>(),
							m_latency};

				for(auto i(0); i < m_result.numclients(); ++i)
					m_result.add_player(
						{this->get_next<std::string>(),
						 this->get_next<std::string>(), this->get_next<int>(),
						 this->get_next<int>(), this->get_next<bool>()});
				m_valid = true;
			}

			template <typename T>
			T get_next()
			{
				auto nullpos(m_workstr.find('\0'));
				if(nullpos == std::string::npos ||
				   nullpos == m_workstr.size() - 1)
					return T{};

				auto result(m_workstr.substr(0, nullpos));
				m_workstr.erase(0, nullpos + 1);
				return mlk::type_utl::to_type<T, std::string>(result);
			}
		};
	}
}

#endif// TWL_NETWORK_INFO_PARSER_HPP
