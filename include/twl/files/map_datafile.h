//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_H
#define TWL_FILES_MAP_DATAFILE_H


#include "map_datafile_items.h"
#include "map_datafile_reader.h"

#include <mlk/containers/container_utl.h>
#include <mlk/tools/enum_utl.h>

#include <vector>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			class map_datafile
			{
				map_datafile_reader m_reader_impl;
				bool m_valid{false};

			public:
				template<typename T>
				map_datafile(const T& file) :
					m_reader_impl{file}
				{
					if(m_reader_impl.exists())
					{
						this->open_read();
						m_valid = m_reader_impl.valid();
					}
				}

				template<item_type type>
				auto find_item()
				-> std::pair<int, int>
				{return m_reader_impl.find_item<type>();}

			private:
				void open_read()
				{
					m_reader_impl.parse_file();
				}

				void open_write()
				{

				}

			public:
				bool valid() const noexcept {return m_valid;}
			};
		}
	}
}


#endif // TWL_FILES_MAP_DATAFILE_H
