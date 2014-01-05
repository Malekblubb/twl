//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
#define TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H


#include "item_base.h"
#include "image.h"

#include <twl/files/map_datafile/map_datafile_types.h>

#include <mlk/graphics/color.h>
#include <mlk/tools/enum_utl.h>


namespace twl
{
	namespace map_itm
	{
		using layer_type = layer_type;


		template<layer_type type>
		class map_layer{public: map_layer() = delete;};

		class map_layer_base
		{
		protected:
			int m_type{0};
			int m_group{0}, m_order{0};
			bool m_detail;
			map_image m_image;
			std::string m_name;

		public:
			map_layer_base(int type, std::string name) :
				m_type{type},
				m_name{std::move(name)}
			{ }

			void set_group_index(int group) noexcept {m_group = group;}
			void set_order(int order) noexcept {m_order = order;}
			void set_detail(bool true_false) noexcept {m_detail = true_false;}
			void set_image(map_image image) noexcept {m_image = std::move(image);}
			void set_name(std::string name) noexcept {m_name = std::move(name);}

			int type() const noexcept {return m_type;} // TODO: layer_type ?
			int group_index() const noexcept {return m_group;}
			int order() const noexcept {return m_order;}
			bool is_detail() const noexcept {return m_detail;}
			const map_image& image() const noexcept {return m_image;}
			std::string name() const noexcept {return m_name;}
		};

		template<>
		class map_layer<layer_type::tiles> : public map_layer_base
		{
			int m_width{100}, m_height{100};
			bool m_is_game_layer{false};
			mlk::gcs::color_rgb m_color;


		public:
			map_layer(bool is_game = false, std::string name = "Tiles") :
				map_layer_base{mlk::enum_utl::to_int(layer_type::tiles), std::move(name)},
				m_is_game_layer{is_game}
			{ }

			void set_width(int width) noexcept {m_width = width;}
			void set_height(int height) noexcept {m_height = height;}
			void set_as_game(bool true_false) noexcept {m_is_game_layer = true_false;}

			int width() const noexcept {return m_width;}
			int height() const noexcept {return m_height;}
			bool is_game_layer() const noexcept {return m_is_game_layer;}
		};


		template<>
		class map_layer<layer_type::quads> : public map_layer_base
		{
			int m_num_quads{0};

		public:
			map_layer(std::string name = "Quads") :
				map_layer_base{mlk::enum_utl::to_int(layer_type::quads), std::move(name)}
			{ }

			int num_quads() const noexcept {return m_num_quads;}
		};
	}
}


#endif // TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
