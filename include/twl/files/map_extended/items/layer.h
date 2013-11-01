//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
#define TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H


#include "item_base.h"
#include "image.h"

#include <twl/files/map_datafile/map_datafile_types.h>

#include <mlk/tools/enum_utl.h>


namespace twl
{
	namespace map_itm
	{
		using layer_type = file::layer_type;

		namespace internal
		{
			class map_layer_base
			{
			protected:
				int m_type{0};
				int m_flags{0};

			public:
				map_layer_base(int type, int flags) :
					m_type{type},
					m_flags{flags}
				{ }

				int type() const noexcept {return m_type;} // TODO: layer_type ?
			};
		}


		template<layer_type type>
		class map_layer{public: map_layer() = delete;};


		template<>
		class map_layer<layer_type::tiles> : public internal::map_layer_base
		{
			int m_width{100}, m_height{100};
			int m_group{0}, m_order{0};
			bool m_detail{false}, m_is_game_layer{false};
			map_image m_image;
			// TODO: color
			std::string m_name{"Tiles"};

		public:
			map_layer(bool is_game) :
				internal::map_layer_base{mlk::enum_utl::to_int(layer_type::tiles), is_game},
				m_is_game_layer{is_game}
			{ }

			void set_width(int width) noexcept {m_width = width;}
			void set_height(int height) noexcept {m_height = height;}
			void set_group_index(int group) noexcept {m_group = group;}
			void set_order(int order) noexcept {m_order = order;}
			void set_detail(bool true_false) noexcept {m_detail = true_false;}
			void set_as_game(bool true_false) noexcept {m_is_game_layer = true_false; m_flags |= true_false;}
			void set_image(map_image image) noexcept {m_image = std::move(image);} // TODO: test performace without move
			void set_name(std::string name) noexcept {m_name = std::move(name);}

			int width() const noexcept {return m_width;}
			int height() const noexcept {return m_height;}
			int group_index() const noexcept {return m_group;}
			int order() const noexcept {return m_order;}
			bool is_detail() const noexcept {return m_detail;}
			bool is_game_layer() const noexcept {return m_is_game_layer;}
			const map_image& image() const noexcept {return m_image;}
			std::string name() const noexcept {return m_name;}
		};


		template<>
		class map_layer<layer_type::quads> : public internal::map_layer_base
		{
			int m_group{0}, m_order{0};
			bool m_detail{false};
			map_image m_image;
			std::string m_name{"Quads"};


		public:
			map_layer() :
				internal::map_layer_base{mlk::enum_utl::to_int(layer_type::quads), 0}
			{ }

			void set_group_index(int group) noexcept {m_group = group;}
			void set_order(int order) noexcept {m_order = order;}
			void set_detail(bool true_false) noexcept {m_detail = true_false;}
			void set_image(map_image image) noexcept {m_image = std::move(image);}
			void set_name(std::string name) noexcept {m_name = std::move(name);}

			int group_index() const noexcept {return m_group;}
			int order() const noexcept {return m_order;}
			bool is_detail() const noexcept {return m_detail;}
			const map_image& image() const noexcept {return m_image;}
			std::string name() const noexcept {return m_name;}
		};
	}
}


#endif // TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
