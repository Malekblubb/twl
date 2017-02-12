//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_NTW_CONSTANTS_HPP
#define TWL_NETWORK_NTW_CONSTANTS_HPP

#include <mlk/network/address.h>
#include <mlk/types/types.h>

#include <cstddef>

namespace twl
{
	// twl
	using masterlist = std::vector<mlk::ntw::ip_address>;
	using econ_command = std::string;

	// internal
	namespace internal
	{
		namespace ntw_constants
		{
			// timeout
			inline constexpr mlk::llong default_timeout() { return 999; }

			// how often should we recheck the server if it is not responding
			inline constexpr mlk::ushort resend_timeouts() { return 0; }

			// max concurrent requests at the same time
			// (one request times out after 'default_timeout' *
			// 'resend_timeouts')
			inline constexpr std::size_t max_concurrent_requests()
			{
				return 20;
			}

			inline constexpr mlk::ullong econ_timeout() { return 5000; }

			inline constexpr std::size_t max_datasize() { return 2048; }

			inline constexpr std::size_t min_interaction_size() { return 14; }

			inline constexpr std::size_t interaction_datasize() { return 8; }

			inline mlk::data_packet ip4_spacer()
			{
				return {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0xff, 0xff};
			}
		}
	}
}

#endif// TWL_NETWORK_NTW_CONSTANTS_HPP
