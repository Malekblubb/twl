//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_AREA_H
#define TWL_FILES_MAP_DATAFILE_AREA_H


#include "map_datafile_items.h"

#include <mlk/containers/container_utl.h>
#include <mlk/types/types.h>

#include <functional>
#include <stdexcept>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			template<typename T>
			class map_datafile_area_base
			{
				using func_t = void(std::vector<T>&);

			protected:
				std::vector<T> m_items;
				std::function<func_t> m_process_fnc;

			public:
				void on_process_data(std::function<func_t> fnc)
				{fnc(m_items);}

				// direct read access to the underlaying data/items
				const std::vector<T>& item_data() const noexcept
				{return m_items;}

				T field(int index) const noexcept
				{
					if(mlk::cnt::is_out_of_bounds(m_items, index))
						throw std::out_of_range("twl::file::internal::map_datafile_area_base::field(): index was out of bounds");
					return m_items[index];
				}
			};

			template<typename T>
			class map_datafile_area : public map_datafile_area_base<T>
			{ };

			template<>
			class map_datafile_area<map_datafile_iteminfo> : public map_datafile_area_base<map_datafile_iteminfo>
			{
			public:
				int start_of_type(int type) const noexcept // TODO: do the types with enum class types
				{
					for(auto& a : m_items)
						if(a.m_type == type)
							return a.m_start;
					return -1;
				}

				int num_type(int type) const noexcept
				{
					int num{0};
					for(auto& a : m_items)
						if(a.m_type == type)
							++num;
					return num;
				}
			};

			template<>
			class map_datafile_area<map_datafile_item> : public map_datafile_area_base<map_datafile_item>
			{
			public:
				int type(int index) const noexcept
				{
					if(mlk::cnt::is_out_of_bounds(m_items, index))
						return -1;
					return m_items[index].type();
				}
				int id(int index) const noexcept
				{
					if(mlk::cnt::is_out_of_bounds(m_items, index))
						return -1;
					return m_items[index].id();
				}
				int size(int index) const noexcept
				{
					if(mlk::cnt::is_out_of_bounds(m_items, index))
						return -1;
					return m_items[index].size();
				}
				const mlk::data_packet& data(int index) const noexcept
				{
					return m_items[index].data();
				}
			};
		}
	}
}


#endif // TWL_FILES_MAP_DATAFILE_AREA_H
