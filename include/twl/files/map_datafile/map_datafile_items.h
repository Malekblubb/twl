//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_ITEMS_H
#define TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_ITEMS_H


#include "map_datafile_types.h"

#include <mlk/containers/container_utl.h>
#include <mlk/types/types.h>

#include <cstring>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			// some PODs for simpler read
			struct map_datafile_header
			{
				char m_sig[4];
				int m_ver;
				int m_size;
				int m_swaplen;
				int m_num_itemtypes;
				int m_num_items;
				int m_num_rawdata;
				int m_item_area_size;
				int m_data_area_size;

				bool valid() const noexcept {return ((std::memcmp(m_sig, "DATA", 4) == 0) && (m_ver == 4));}
				int body_size() const noexcept
				{
					return (m_num_itemtypes * 12) +
							(m_num_items * sizeof(int)) +
							((m_num_rawdata * sizeof(int)) * 2) +
							m_item_area_size + m_data_area_size;
				}
			};

			struct map_datafile_iteminfo
			{
				int m_type;
				int m_start;
				int m_num;
			};

			class map_datafile_item
			{
				int m_type;
				int m_id;
				int m_size;
				mlk::data_packet m_data;

			public:
				map_datafile_item() = default;
				map_datafile_item(int type_and_id, int size, const mlk::data_packet& data) noexcept :
					m_type{(type_and_id >> 16) & 0xff},
					m_id{type_and_id & 0xff},
					m_size{size},
					m_data(data)
				{ }
				map_datafile_item(map_datafile_item&& o) noexcept = default;
				map_datafile_item(const map_datafile_item& o) = default;
				map_datafile_item& operator=(const map_datafile_item& o) = default;

				int type() const noexcept {return m_type;}
				int id() const noexcept {return m_id;}
				int size() const noexcept {return m_size;}
				const mlk::data_packet& data() const noexcept {return m_data;}
			};

			template<typename T>
			T make_item(const mlk::data_packet& data)
			{return *reinterpret_cast<const T*>(data.data());}

			class map_datafile_color
			{
				int m_r, m_g, m_b, m_a;

			public:
				int red() const noexcept {return m_r;}
				int green() const noexcept {return m_g;}
				int blue() const noexcept {return m_b;}
				int alpha() const noexcept {return m_a;}
			};

			class map_datafile_point
			{
				int m_x, m_y;

			public:
				int x() const noexcept {return m_x;}
				int y() const noexcept {return m_y;}
			};

			class map_datafile_info
			{
				int m_author;
				int m_map_version;
				int m_credits;
				int m_license;

			public:
				// construct with an item
				map_datafile_info(const map_datafile_item& item)
				{*this = make_item<map_datafile_info>(item.data());}

				int author() const noexcept {return m_author;}
				int map_version() const noexcept {return m_map_version;}
				int credits() const noexcept {return m_credits;}
				int license() const noexcept {return m_license;}
			};

			class map_datafile_image
			{
				int m_width;
				int m_height;
				int m_external;
				int m_image_name;
				int m_image_data;

			public:
				map_datafile_image(const map_datafile_item& item)
				{*this = make_item<map_datafile_image>(item.data());}

				int width() const noexcept {return m_width;}
				int height() const noexcept {return m_height;}
				int external() const noexcept {return m_external;}
				int name() const noexcept {return m_image_name;}
				int data() const noexcept {return m_image_data;}
			};

			class map_datafile_group
			{
				int m_offset_x, m_offset_y;
				int m_para_x, m_para_y;
				int m_start_layer;
				int m_num_layers;
				int m_clipping;
				int m_clip_x, m_clip_y, m_clip_w, m_clip_h;
				// TODO: impl name

			public:
				map_datafile_group(const map_datafile_item& item)
				{*this = make_item<map_datafile_group>(item.data());}

				int offset_x() const noexcept {return m_offset_x;}
				int offset_y() const noexcept {return m_offset_y;}
				int para_x() const noexcept {return m_para_x;}
				int para_y() const noexcept {return m_para_y;}
				int start_layer() const noexcept {int ret = m_num_layers > 0 ?  m_start_layer : -1; return ret;}
				int num_layers() const noexcept {return m_num_layers;}
				int clipping() const noexcept {return m_clipping;}
				int clip_x() const noexcept {return m_clip_x;}
				int clip_y() const noexcept {return m_clip_y;}
				int clip_w() const noexcept {return m_clip_w;}
				int clip_h() const noexcept {return m_clip_h;}
			};

			class basic_map_datafile_layer
			{
				int m_type;
				int m_flags;

			public:
				basic_map_datafile_layer(const map_datafile_item& item)
				{*this = make_item<basic_map_datafile_layer>(item.data());}

				int type() const noexcept {return m_type;}
				int flags() const noexcept {return m_flags;}
			};

			template<layer_type type>
			class map_datafile_layer
			{public: map_datafile_layer() = delete;};

			template<>
			class map_datafile_layer<layer_type::tiles> : public basic_map_datafile_layer
			{
				int m_width;
				int m_height;
				int m_flags;
				map_datafile_color m_color;
				int m_color_env;
				int m_color_env_offs;
				int m_image;
				int m_data;
				// TODO: impl name

			public:
				map_datafile_layer(const map_datafile_item& item) :
					basic_map_datafile_layer{item}
				{ }

				int width() const noexcept {return m_width;}
				int height() const noexcept {return m_height;}
				int flags() const noexcept {return m_flags;}
				int color_env() const noexcept {return m_color_env;}
				int color_env_offs() const noexcept {return m_color_env_offs;}
				int image() const noexcept {return m_image;}
				int data() const noexcept {return m_data;}
			};

			template<>
			class map_datafile_layer<layer_type::quads> : public basic_map_datafile_layer
			{
				int m_num_quads;
				int m_data;
				int m_image;
				// TODO: impl name

			public:
				map_datafile_layer(const map_datafile_item& item) :
					basic_map_datafile_layer{item}
				{ }

				int num_quads() const noexcept {return m_num_quads;}
				int data() const noexcept {return m_data;}
				int image() const noexcept {return m_image;}
			};

			class map_datafile_quad
			{
				map_datafile_point m_points[5];
				map_datafile_color m_colors[4];
				map_datafile_point m_texcoords[4];

				int m_pos_env;
				int m_pos_env_offs;
				int m_color_env;
				int m_color_env_offs;

			public:
				map_datafile_quad(const map_datafile_item& item)
				{*this = make_item<map_datafile_quad>(item.data());}
			};

			class map_datafile_tile
			{
				unsigned char m_index, m_flags, m_skip, m_reserved;

			public:
				map_datafile_tile(const mlk::data_packet& data)
				{*this = make_item<map_datafile_tile>(data);}
			};
		}
	}
}



#endif // TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_ITEMS_H
