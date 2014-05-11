//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_LAYER_TILES_H
#define TWL_FILES_MAP_MAP_LAYER_TILES_H


#include "basic_map_layer.hpp"
#include "map_datafile_items.hpp"
#include "map_image.hpp"

#include <mlk/graphics/color.h>

#include <map>


namespace twl
{
	class map_layer_tiles : public internal::basic_map_layer
	{
		friend class map;

		mlk::st m_width{0}, m_height{0};
		mlk::gcs::color_rgb m_color;
		const map_image* m_image{nullptr};
		std::vector<internal::tile> m_tiles;
		std::string m_name;

		map_layer_tiles(const internal::map_datafile_layer_tilemap* tlm, const std::vector<mlk::data_packet>& uncomoressed_data, const std::vector<map_image>& images) :
			internal::basic_map_layer{map_constants::layer_type::tiles},
			m_width{static_cast<mlk::st>(tlm->width)},
			m_height{static_cast<mlk::st>(tlm->height)},
			m_color{tlm->col},
			m_image{tlm->image >= 0 ? &images.at(tlm->image) : nullptr},
			m_tiles(m_width * m_height),
			m_name{tlm->version > 2 ? map_constants::ints_to_str(tlm->name, 3) : "Tiles"}
		{
			if((tlm->data >= 0) && uncomoressed_data[tlm->data].size() / sizeof(internal::tile) == m_width * m_height)
			{
				// add the tiles
				mlk::data_packet tmp(sizeof(internal::tile));
				for(auto i(0); i < uncomoressed_data[tlm->data].size(); i += sizeof(internal::tile))
				{
					tmp = {std::begin(uncomoressed_data[tlm->data]) + i, std::begin(uncomoressed_data[tlm->data]) + i + sizeof(internal::tile)};
					m_tiles[i / sizeof(internal::tile)] = *reinterpret_cast<const internal::tile*>(tmp.data());
				}
			}
		}

	public:
		map_layer_tiles() = default;

		auto width() const noexcept
		{return m_width;}

		auto height() const noexcept
		{return m_height;}

		const auto& color() const noexcept
		{return m_color;}

		const auto* image() const noexcept
		{return m_image;}

		auto has_image() const noexcept
		{return m_image != nullptr;}

		const auto& tiles() const noexcept
		{return m_tiles;}

		const auto& name() const noexcept
		{return m_name;}
	};
}


#endif // TWL_FILES_MAP_MAP_LAYER_TILES_H

