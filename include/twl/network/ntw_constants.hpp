//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_NTW_CONSTANTS_HPP
#define TWL_NETWORK_NTW_CONSTANTS_HPP


#include <cstddef>


namespace twl
{
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
		}
	}
}


#endif // TWL_NETWORK_NTW_CONSTANTS_HPP
