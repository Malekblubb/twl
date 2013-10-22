//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_ITEMS_H
#define TWL_FILES_MAP_DATAFILE_ITEMS_H


#include <mlk/types/types.h>

#include <cstring>

#include <iostream>

namespace twl
{
	namespace file
	{
		namespace internal
		{
			// some PODs for simpler read
			struct map_datafile_header
			{
				char m_sig[4];
				int m_ver;
				int m_size;
				int m_swaplen;
				int m_num_itemtypes;
				int m_num_items;
				int m_num_rawdata;
				int m_item_area_size;
				int m_data_area_size;

				bool valid() const noexcept {return ((std::memcmp(m_sig, "DATA", 4) == 0) && (m_ver == 4));}
				int body_size() const noexcept
				{
					return (m_num_itemtypes * 12) +
							(m_num_items * sizeof(int)) +
							((m_num_rawdata * sizeof(int)) * 2) +
							m_item_area_size + m_data_area_size;
				}
			};

			struct map_datafile_iteminfo
			{
				int m_type;
				int m_start;
				int m_num;
			};

			struct basic_map_datafile_item
			{
				int m_type_and_id;
				int m_size;
			};


			class map_datafile_item
			{
				int m_type;
				int m_id;
				int m_size;
				mlk::data_packet m_data;

			public:
				map_datafile_item() = default;
				map_datafile_item(int type_and_id, int size, const mlk::data_packet& data) noexcept :
					m_type{(type_and_id >> 16) & 0xff},
					m_id{type_and_id & 0xff},
					m_size{size},
					m_data(data)
				{ }
				map_datafile_item(map_datafile_item&& o) noexcept = default;

				int type() const noexcept {return m_type;}
				int id() const noexcept {return m_id;}
				int size() const noexcept {return m_size;}
				const mlk::data_packet& data() const noexcept {return m_data;}
			};
		}
	}
}



#endif // TWL_FILES_MAP_DATAFILE_ITEMS_H
