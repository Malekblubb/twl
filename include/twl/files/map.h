//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_H
#define TWL_FILES_MAP_H


#include "map_datafile.h"


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
			{ }
		};
	}
}



#endif // TWL_FILES_MAP_H
