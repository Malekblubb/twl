//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_INFO_H
#define TWL_NETWORK_SERVER_INFO_H


#include "basic_server_info.h"
#include "info_decoder.h"

#include <mlk/types/types.h>

#include <string>


namespace twl
{
	class server_info;
	namespace internal
	{server_info make_info(const mlk::data_packet&);}

	class server_info
	{
		internal::basic_server_info m_basic_info;

		friend server_info internal::make_info(const mlk::data_packet&);
		server_info(const internal::basic_server_info& basic_info) :
			m_basic_info(basic_info)
		{ }

	public:
		server_info() = default;

		// getters
		const auto name() const noexcept -> decltype((m_basic_info.m_name)) {return m_basic_info.m_name;}
		const auto game_type() const noexcept -> decltype((m_basic_info.m_game_type)) {return m_basic_info.m_game_type;}
	};

	namespace internal
	{
		server_info make_info(const mlk::data_packet& data)
		{
			basic_server_info basic;
			decode_server_info(data, basic);
			return {basic};
		}
	}
}


#endif // TWL_NETWORK_SERVER_INFO_H
