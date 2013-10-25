//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_H
#define TWL_FILES_MAP_DATAFILE_H


#include "map_datafile_items.h"
#include "map_datafile_reader.h"

#include <mlk/containers/container_utl.h>

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
				map_datafile_header m_header{{0}};

			public:
				template<typename T>
				map_datafile(const T& file) :
					m_reader_impl{file}
				{this->open();}


				void open()
				{
					this->open_read();
				}

			private:
				void open_read()
				{
					m_reader_impl.parse_file();
				}
			};
		}
	}
}


#endif // TWL_FILES_MAP_DATAFILE_H
