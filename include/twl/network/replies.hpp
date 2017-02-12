//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_REPLIES_HPP
#define TWL_NETWORK_REPLIES_HPP

#include "ntw_constants.hpp"

#include <mlk/containers/container_utl.h>

namespace twl
{
	namespace internal
	{
		enum class server_reply : char
		{
			game_info,

			master_list,
			master_count
		};

		class reply_base
		{
			mlk::data_packet m_data;

		public:
			reply_base(mlk::data_packet&& data) : m_data{std::move(data)} {}

			const mlk::data_packet& operator()() const noexcept
			{
				return m_data;
			}
		};

		template <server_reply>
		struct reply;

		template <>
		struct reply<server_reply::game_info> : public reply_base
		{
			reply() : reply_base{{0xff, 0xff, 0xff, 0xff, 'i', 'n', 'f', '3'}}
			{
			}
		};

		template <>
		struct reply<server_reply::master_list> : public reply_base
		{
			reply() : reply_base{{0xff, 0xff, 0xff, 0xff, 'l', 'i', 's', '2'}}
			{
			}
		};

		template <>
		struct reply<server_reply::master_count> : public reply_base
		{
			reply() : reply_base{{0xff, 0xff, 0xff, 0xff, 's', 'i', 'z', '2'}}
			{
			}
		};

		// checks if a >connless< packet contains the requested reply
		template <server_reply rep>
		bool is_reply(const mlk::data_packet& data)
		{
			return data.size() >= ntw_constants::interaction_datasize() &&
				   reply<rep>{}() == mlk::data_packet{std::begin(data) + 6,
													  std::begin(data) + 14};
		}
	}
}

#endif// TWL_NETWORK_REPLIES_HPP
