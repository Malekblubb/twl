//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_DATAFILE_ITEMS_H
#define TWL_FILES_MAP_MAP_DATAFILE_ITEMS_H


#include <mlk/types/types.h>

#include <cstring>


namespace twl
{
	namespace internal
	{
		struct map_datafile_header
		{
			char sig[4];
			int ver;
			int size;
			int swaplen;
			int num_itemtypes;
			int num_items;
			int num_rawdata;
			int item_area_size;
			int data_area_size;

			bool valid() const noexcept
			{return ((std::memcmp(sig, "DATA", 4) == 0) && (ver == 4));}

			int body_size() const noexcept
			{
				return (num_itemtypes * 12) +
						(num_items * sizeof(int)) +
						((num_rawdata * sizeof(int)) * 2) +
						item_area_size + data_area_size;
			}
		};

		struct map_datafile_iteminfo
		{
			int type;
			int start;
			int num;
		};

		struct map_datafile_item
		{
			int type;
			int id;
			mlk::data_packet data;
		};


		//

		struct color
		{
			int r, g, b, a;
		};

		struct basic_map_datafile_item
		{
			int type_and_id;
			int length;
		};

		struct map_datafile_version
		{
			int version;
		};

		struct map_datafile_info
		{
			int version;
			int author;
			int map_version;
			int credits;
			int license;
		};

		struct map_datafile_image
		{
			int version;
			int width;
			int height;
			int external;
			int image_name;
			int image_data;
		};

		struct map_datafile_group
		{
			int version;
			int offset_x;
			int offset_y;
			int parallax_x;
			int parallax_y;
			int startlayer;
			int numlayers;
			int use_clipping;
			int clip_x;
			int clip_y;
			int clip_w;
			int clip_h;
			int name[3];
		};

		struct map_datafile_layer
		{
			int version;
			int type;
			int flags;
		};

		struct map_datafile_layer_tilemap
		{
			map_datafile_layer layer;
			int version;
			int width;
			int height;
			int flags;
			color col;
			int colorenv;
			int colorenv_offset;
			int image;
			int data;
			int name[3];
		};

		struct map_datafile_layer_quads
		{
			map_datafile_layer layer;
			int version;
			int num_quads;
			int data;
			int image;
			int name[3];
		};

		struct map_datafile_envpoint
		{
			int time;
			int curevetype;
			int values[4];
		};

		struct map_datafile_envelope
		{
			int version;
			int channels;
			int startpoint;
			int numpoints;
			int name[3];
			int syncron;
		};
	}
}


#endif // TWL_FILES_MAP_MAP_DATAFILE_ITEMS_H

