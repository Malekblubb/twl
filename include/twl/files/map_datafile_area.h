//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_AREA_H
#define TWL_FILES_MAP_DATAFILE_AREA_H


#include <mlk/containers/container_utl.h>
#include <mlk/types/types.h>

#include "map_datafile_items.h"
#include <functional>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			template<typename T>
			class map_datafile_area_base
			{
				using func_t = std::vector<T>();

			protected:
				std::vector<T> m_items;
				mlk::data_packet m_data;
				std::function<func_t> m_process_fnc;

			public:
				void on_process_data(mlk::data_packet& data, std::function<func_t> fnc)
				{
					m_data = data; // take the reference
					m_process_fnc = fnc;
					this->process_data();
				}

				void process_data()
				{
					m_items = m_process_fnc();
				}

				// direct read access to the underlaying data/items
				const std::vector<T>& data() const noexcept
				{return m_items;}

				int field(int index) const noexcept
				{
					if(mlk::cnt::is_out_of_bounds(m_items, index))
						return -1;
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
