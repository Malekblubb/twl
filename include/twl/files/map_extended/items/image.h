//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_IMAGE_GROUP_H
#define TWL_FILES_MAP_EXTENDED_IMAGE_GROUP_H


#include "item_base.h"

#include <mlk/types/types.h>

#include <string>


namespace twl
{
	namespace map_itm
	{
		class map_image : public internal::map_item_base
		{
			mlk::data_packet m_data;
			int m_height{0}, m_width{0};
			bool m_external{true};
			std::string m_name{"unnamed-image"};

		public:
			map_image() = default;

			map_image(const mlk::data_packet& data, int height, int width) :
				m_data(data),
				m_height{height},
				m_width{width}
			{ }

			void set_height(int height) noexcept {m_height = height;}
			void set_width(int width) noexcept {m_width = width;}
			void external(bool true_false) noexcept {m_external = true_false;}
			void set_name(const std::string& name) noexcept {m_name = name;}

			int height() const noexcept {return m_height;}
			int width() const noexcept {return m_width;}
			bool external() const noexcept {return m_external;}
			std::string name() const noexcept {return m_name;}
		};
	}
}



#endif // TWL_FILES_MAP_EXTENDED_IMAGE_GROUP_H
