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

			class map_datafile_info
			{
				int m_author;
				int m_map_version;
				int m_credits;
				int m_license;

			public:
				// construct with an item
				map_datafile_info(const map_datafile_item& item) :
					map_datafile_info{item.data()}
				{ }

				map_datafile_info(const mlk::data_packet& data) :
					m_author{mlk::cnt::make_int(4, data)},
					m_map_version{mlk::cnt::make_int(8, data)},
					m_credits{mlk::cnt::make_int(12, data)},
					m_license{mlk::cnt::make_int(16, data)}
				{ }

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
				map_datafile_image(const map_datafile_item& item) :
					map_datafile_image{item.data()}
				{ }

				map_datafile_image(const mlk::data_packet& data) :
					m_width{mlk::cnt::make_int(4, data)},
					m_height{mlk::cnt::make_int(8, data)},
					m_external{mlk::cnt::make_int(12, data)},
					m_image_name{mlk::cnt::make_int(16, data)},
					m_image_data{mlk::cnt::make_int(20, data)}
				{ }

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
				map_datafile_group(const map_datafile_item& item) :
					map_datafile_group{item.data()}
				{ }

				map_datafile_group(const mlk::data_packet& data) :
					m_offset_x{mlk::cnt::make_int(4, data)},
					m_offset_y{mlk::cnt::make_int(8, data)},
					m_para_x{mlk::cnt::make_int(12, data)},
					m_para_y{mlk::cnt::make_int(16, data)},
					m_start_layer{mlk::cnt::make_int(20, data)},
					m_num_layers{mlk::cnt::make_int(24, data)},
					m_clipping{mlk::cnt::make_int(28, data)},
					m_clip_x{mlk::cnt::make_int(32, data)},
					m_clip_y{mlk::cnt::make_int(36, data)},
					m_clip_w{mlk::cnt::make_int(40, data)},
					m_clip_h{mlk::cnt::make_int(44, data)}
				{ }

				int offset_x() const noexcept {return m_offset_x;}
				int offset_y() const noexcept {return m_offset_y;}
				int para_x() const noexcept {return m_para_x;}
				int para_y() const noexcept {return m_para_y;}
				int start_layer() const noexcept {return m_start_layer;}
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
				basic_map_datafile_layer(const map_datafile_item& item) :
					basic_map_datafile_layer{item.data()}
				{ }

				basic_map_datafile_layer(const mlk::data_packet& data) :
					m_type{mlk::cnt::make_int(4, data)},
					m_flags{mlk::cnt::make_int(8, data)}
				{ }

				int type() const noexcept {return m_type;}
				int flags() const noexcept {return m_flags;}
			};

			template<layer_type type>
			class map_datafile_layer
			{public: map_datafile_layer() = delete;};

			template<>
			class map_datafile_layer<layer_type::tiles>
			{
				int m_width;
				int m_height;
				int m_flags;
				// TODO: impl color
				int m_color_env;
				int m_color_env_offs;
				int m_image;
				int m_data;
				// TODO: impl name

			public:
				map_datafile_layer(const map_datafile_item& item) :
					map_datafile_layer{item.data()}
				{ }

				map_datafile_layer(const mlk::data_packet& data) :
					m_width{mlk::cnt::make_int(16, data)},
					m_height{mlk::cnt::make_int(20, data)},
					m_flags{mlk::cnt::make_int(24, data)},
					m_color_env{mlk::cnt::make_int(40, data)},
					m_color_env_offs{mlk::cnt::make_int(44, data)},
					m_image{mlk::cnt::make_int(48, data)},
					m_data{mlk::cnt::make_int(52, data)}
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
			class map_datafile_layer<layer_type::quads>
			{
				int m_num_quads;
				int m_data;
				int m_image;
				// TODO: impl name

			public:
				map_datafile_layer(const map_datafile_item& item) :
					map_datafile_layer{item.data()}
				{ }

				map_datafile_layer(const mlk::data_packet& data) :
					m_num_quads{mlk::cnt::make_int(16, data)},
					m_data{mlk::cnt::make_int(20, data)},
					m_image{mlk::cnt::make_int(24, data)}
				{ }

				int num_quads() const noexcept {return m_num_quads;}
				int data() const noexcept {return m_data;}
				int image() const noexcept {return m_image;}
			};
		}
	}
}



#endif // TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_ITEMS_H
