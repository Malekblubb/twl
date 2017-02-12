//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_BASIC_MAP_LAYER_H
#define TWL_FILES_MAP_BASIC_MAP_LAYER_H

#include "map_constants.hpp"

namespace twl
{
	namespace internal
	{
		class basic_map_layer
		{
			map_constants::layer_type m_type;

		public:
			basic_map_layer(map_constants::layer_type type =
								map_constants::layer_type::invalid)
				: m_type{type}
			{
			}

			auto type() const noexcept { return m_type; }
		};
	}
}

#endif// TWL_FILES_MAP_BASIC_MAP_LAYER_H
