//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_ITEMS_H
#define TWL_FILES_MAP_DATAFILE_ITEMS_H


#include <cstring>


namespace twl
{
	namespace internal
	{
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

			bool valid() const noexcept
			{return ((std::memcmp(m_sig, "DATA", 4) == 0) && (m_ver == 4));}

			int body_size() const noexcept
			{
				return (m_num_itemtypes * 12) +
						(m_num_items * sizeof(int)) +
						((m_num_rawdata * sizeof(int)) * 2) +
						m_item_area_size + m_data_area_size;
			}
		};
	}
}


#endif // TWL_FILES_MAP_DATAFILE_ITEMS_H

