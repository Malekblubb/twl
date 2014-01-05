//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_TYPES_H
#define TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_TYPES_H


namespace twl
{
	enum class item_type : int
	{
		version = 0,
		info,
		image,
		envelope,
		group,
		layer,
		envpoints
	};

	enum class layer_type : int
	{
		invalid = 0,
		game,
		tiles,
		quads,

		base
	};

	enum class layer_flags : int
	{detail = 1};

	enum class tile_layer_flags : int
	{is_game_layer = 1};
}


#endif // TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_TYPES_H
