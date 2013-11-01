//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_ITEMS_GROUP_H
#define TWL_FILES_MAP_EXTENDED_ITEMS_GROUP_H


#include "item_base.h"
#include "layer.h"

#include <memory>
#include <string>
#include <vector>


namespace twl
{
	namespace map_itm
	{
		class map_group : public internal::map_item_base
		{
			// layer
			using vec = std::vector<std::shared_ptr<map_layer<layer_type::base>>>;
			vec m_layers;

			// sepcs
			int m_order;
			int m_pos_x, m_pos_y;
			int m_para_x, m_para_y;
			bool m_clipping;
			int m_clip_x, m_clip_y, m_clip_w, m_clip_h;
			std::string	m_name;


		public:
			map_group() = default;

			template<typename T>
			void add_layer(const T& layer) noexcept
			{
				static_assert(std::is_same<T, map_layer<layer_type::tiles>>::value ||
							  std::is_same<T, map_layer<layer_type::quads>>::value, "invalid type passed to twl::file::map_group::add_layer<T>");
				m_layers.push_back(std::static_pointer_cast<map_layer<layer_type::base>>(layer));
			}

			template<typename T>
			const T& layer_as(int index) const // TODO: add here some type- and bounds checking
			{return std::static_pointer_cast<T>(m_layers.at(index));}

			const vec& layers() const noexcept {return m_layers;}

			void set_order(int order) noexcept {m_order = order;}
			void set_pos_x(int pos_x) noexcept {m_pos_x = pos_x;}
			void set_pos_y(int pos_y) noexcept {m_pos_y = pos_y;}
			void set_para_x(int para_x) noexcept {m_para_x = para_x;}
			void set_para_y(int para_y) noexcept {m_para_y = para_y;}
			void set_clipping(bool on_off) noexcept {m_clipping = on_off;}
			void set_clip_x(int clip_x) noexcept {m_clip_x = clip_x;}
			void set_clip_y(int clip_y) noexcept {m_clip_y = clip_y;}
			void set_clip_w(int clip_w) noexcept {m_clip_w = clip_w;}
			void set_clip_h(int clip_h) noexcept {m_clip_h = clip_h;}

			int order() const noexcept {return m_order;}
			int pos_x() const noexcept {return m_pos_x;}
			int pos_y() const noexcept {return m_pos_y;}
			int para_x() const noexcept {return m_para_x;}
			int para_y() const noexcept {return m_para_y;}
			bool clipping() const noexcept {return m_clipping;}
			int clip_x() const noexcept {return m_clip_x;}
			int clip_y() const noexcept {return m_clip_y;}
			int clip_w() const noexcept {return m_clip_w;}
			int clip_h() const noexcept {return m_clip_h;}
		};
	}
}

#endif // TWL_FILES_MAP_EXTENDED_ITEMS_GROUP_H