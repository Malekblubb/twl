//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_CONSTANTS_H
#define TWL_FILES_MAP_MAP_CONSTANTS_H


#include "map_datafile_items.hpp"


namespace twl
{
	namespace map_constants
	{
		enum item_type
		{
			version = 0,
			info,
			image,
			envelope,
			group,
			layer,
			envpoint,

			layer_tiles,
			layer_quads
		};

		enum layer_type
		{
			invalid = 0,
			game,
			tiles,
			quads
		};


		template<item_type type>
		struct get_item_type{ };

		template<>
		struct get_item_type<item_type::version>
		{using type = internal::map_datafile_version;};

		template<>
		struct get_item_type<item_type::info>
		{using type = internal::map_datafile_info;};

		template<>
		struct get_item_type<item_type::image>
		{using type = internal::map_datafile_image;};

		template<>
		struct get_item_type<item_type::envelope>
		{using type = internal::map_datafile_envelope;};

		template<>
		struct get_item_type<item_type::group>
		{using type = internal::map_datafile_group;};

		template<>
		struct get_item_type<item_type::layer>
		{using type = internal::map_datafile_layer;};

		template<>
		struct get_item_type<item_type::envpoint>
		{using type = internal::map_datafile_envpoint;};

		template<>
		struct get_item_type<item_type::layer_tiles>
		{using type = internal::map_datafile_layer_tilemap;};

		template<>
		struct get_item_type<item_type::layer_quads>
		{using type = internal::map_datafile_layer_quads;};
	}
}


#endif // TWL_FILES_MAP_MAP_CONSTANTS_H
