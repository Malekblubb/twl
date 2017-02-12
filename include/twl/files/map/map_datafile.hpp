//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_DATAFILE_H
#define TWL_FILES_MAP_MAP_DATAFILE_H

#include "map_constants.hpp"
#include "map_datafile_items.hpp"

#include <mlk/containers/container_utl.h>
#include <mlk/types/types.h>

namespace twl
{
	namespace internal
	{
		class map_datafile
		{
			// items
			std::vector<map_datafile_item> m_items;

			// uncompressed data
			std::vector<mlk::data_packet> m_uncomressed_data;

		public:
			void add_item(const map_datafile_item& item)
			{
				m_items.emplace_back(item);
			}

			void add_uncompressed_data(std::vector<mlk::data_packet>& data)
			{
				m_uncomressed_data = std::move(data);
			}

			template <map_constants::item_type type>
			mlk::st num_items_of_type() const
			{
				mlk::st result{0};
				for(const auto& a : m_items)
					if(a.type == type) ++result;
				return result;
			}

			template <map_constants::item_type type,
					  typename Item_Type =
						  typename map_constants::get_item_type<type>::type>
			std::vector<const Item_Type*> items_of_type() const
			{
				std::vector<const Item_Type*> result;
				for(const auto& a : m_items)
					if(a.type == type)
						result.push_back(
							reinterpret_cast<const Item_Type*>(a.data.data()));
				return result;
			}

			template <map_constants::item_type type,
					  typename Item_Type =
						  typename map_constants::get_item_type<type>::type>
			const Item_Type* item(int id) const
			{
				for(const auto& a : m_items)
					if(a.type == type && a.id == id)
						return reinterpret_cast<const Item_Type*>(
							a.data.data());
				return nullptr;
			}

			const auto& uncompressed_data() const noexcept
			{
				return m_uncomressed_data;
			}

			auto valid() const noexcept { return !m_uncomressed_data.empty(); }

			void clear()
			{
				mlk::cnt::free_vec(m_items);
				mlk::cnt::free_vec(m_uncomressed_data);
			}
		};

		// tiles
		template <>
		inline std::vector<const map_datafile_layer_tilemap*>
		map_datafile::items_of_type<map_constants::item_type::layer_tiles,
									map_datafile_layer_tilemap>() const
		{
			std::vector<const map_datafile_layer_tilemap*> result;
			for(const auto& a : m_items) {
				if(a.type == map_constants::item_type::layer) {
					// cast the data
					auto* ptr(reinterpret_cast<const map_datafile_layer*>(
						a.data.data()));
					if(ptr == nullptr) return result;

					// is this the right layer type ?
					if(ptr->type == map_constants::layer_type::tiles)
						result.push_back(
							reinterpret_cast<const map_datafile_layer_tilemap*>(
								a.data.data()));
				}
			}
			return result;
		}

		// quads
		template <>
		inline std::vector<const map_datafile_layer_quads*>
		map_datafile::items_of_type<map_constants::item_type::layer_quads,
									map_datafile_layer_quads>() const
		{
			std::vector<const map_datafile_layer_quads*> result;
			for(const auto& a : m_items) {
				if(a.type == map_constants::item_type::layer) {
					// cast the data
					auto* ptr(reinterpret_cast<const map_datafile_layer*>(
						a.data.data()));
					if(ptr == nullptr) return result;

					// is this the right layer type ?
					if(ptr->type == map_constants::layer_type::quads)
						result.push_back(
							reinterpret_cast<const map_datafile_layer_quads*>(
								a.data.data()));
				}
			}
			return result;
		}
	}
}

#endif// TWL_FILES_MAP_MAP_DATAFILE_H
