//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_H
#define TWL_FILES_MAP_H


#include "map_datafile.h"
#include "map_datafile_types.h"


namespace twl
{
	namespace file
	{
		class map
		{
			internal::map_datafile m_datafile;


		public:
			template<typename T>
			map(const T& file) :
				m_datafile{file}
			{
				std::cout << m_datafile.find_item<item_type::group>().second << std::endl;
			}
		};
	}
}



#endif // TWL_FILES_MAP_H
