//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_H
#define TWL_FILES_MAP_MAP_H


#include "basic_map_layer.hpp"
#include "map_datafile_manager.hpp"
#include "map_group.hpp"
#include "map_image.hpp"
#include "map_info.hpp"
#include "map_layer_quads.hpp"
#include "map_layer_tiles.hpp"


namespace twl
{
	class map
	{
		internal::map_datafile_manager m_datafilemanager;

		// info
		map_info m_info;

		// items
		// images
		std::vector<map_image> m_images;

		// layers
		std::vector<mlk::sptr<internal::basic_map_layer>> m_layers;

		// groups
		std::vector<map_group> m_groups;

	public:
		map() = default;

		map(const std::string& path) :
			m_datafilemanager{path}
		{ }

		bool open()
		{
			auto succ(m_datafilemanager.open());
			this->construct_items();
			return succ;
		}

		bool open(const std::string& path)
		{
			auto succ(m_datafilemanager.open(path));
			this->construct_items();
			return succ;
		}

		void close()
		{
			m_datafilemanager.close();
			mlk::cnt::free_vec(m_images);
			mlk::cnt::free_vec(m_layers);
			mlk::cnt::free_vec(m_groups);
		}

		const auto& info() const noexcept
		{return m_info;}

		const auto& images() const noexcept
		{return m_images;}

		const auto& layers() const noexcept
		{return m_layers;}

		const auto& groups() const noexcept
		{return m_groups;}

	private:
		void construct_items()
		{
			const auto& result(m_datafilemanager.parser().result());
			const auto& uncompressed_data(result.uncompressed_data());

			// info
			auto info(result.items_of_type<map_constants::item_type::info>());
			if(info.size() == 1)
				m_info = {info[0], uncompressed_data};

			// images
			for(const auto& a : result.items_of_type<map_constants::item_type::image>())
				m_images.emplace_back(map_image{a, uncompressed_data});

			// layers
			for(const auto& a : result.items_of_type<map_constants::item_type::layer>())
			{
				if(a->type == map_constants::layer_type::game)
					m_layers.emplace_back(new internal::basic_map_layer{map_constants::layer_type::game});

				else if(a->type == map_constants::layer_type::tiles)
					m_layers.emplace_back(new map_layer_tiles{reinterpret_cast<const internal::map_datafile_layer_tilemap*>(a), uncompressed_data, m_images});

				else if(a->type == map_constants::layer_type::quads)
					m_layers.emplace_back(new map_layer_quads{reinterpret_cast<const internal::map_datafile_layer_quads*>(a), uncompressed_data, m_images});
			}

			// groups
			for(const auto& a : result.items_of_type<map_constants::item_type::group>())
				m_groups.emplace_back(map_group{a, m_layers});
		}
	};
}


#endif // TWL_FILES_MAP_MAP_H
