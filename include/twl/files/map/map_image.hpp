//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_IMAGE_H
#define TWL_FILES_MAP_MAP_IMAGE_H


#include "map_datafile_items.hpp"

#include <string>


namespace twl
{
	class map_image
	{
		friend class map;

		std::string m_name;
		mlk::st m_width{0}, m_height{0};
		bool m_external{true};
		mlk::data_packet m_data;

		map_image(const internal::map_datafile_image* img, const std::vector<mlk::data_packet>& uncompressed_data) :
			m_name{reinterpret_cast<const char*>(uncompressed_data[img->image_name].data())},
			m_width{static_cast<mlk::st>(img->width)},
			m_height{static_cast<mlk::st>(img->height)},
			m_external{static_cast<bool>(img->external)},
			m_data{uncompressed_data[img->image_data]}
		{ }

	public:
		map_image() = default;

		const auto& name() const noexcept
		{return m_name;}

		auto width() const noexcept
		{return m_width;}

		auto height() const noexcept
		{return m_height;}

		auto external() const noexcept
		{return m_external;}

		const auto& data() const noexcept
		{return m_data;}
	};
}


#endif // TWL_FILES_MAP_MAP_IMAGE_H
