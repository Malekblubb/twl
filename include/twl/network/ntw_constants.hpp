//
// Copyright (c) 2013-2014 Christoph Malek
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

	// internal
	namespace internal
	{
		namespace ntw_constants
		{			
			inline constexpr long long default_timeout()
			{return 999;}

			inline constexpr std::size_t max_datasize()
			{return 2048;}

			inline constexpr std::size_t min_interaction_size()
			{return 14;}

			inline constexpr std::size_t interaction_datasize()
			{return 8;}

			inline mlk::data_packet ip4_spacer()
			{return {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff};}
		}
	}
}


#endif // TWL_NETWORK_NTW_CONSTANTS_HPP
