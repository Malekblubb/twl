//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_H
#define TWL_FILES_MAP_MAP_H


#include "map_datafile.hpp"


namespace twl
{
	class map
	{
		map_datafile m_datafile;

	public:
		map() = default;

		map(const std::string& path) :
			m_datafile{path}
		{ }

		bool open()
		{
			return m_datafile.open();
		}

		bool open(const std::string& path)
		{
			return m_datafile.open(path);
		}
	};
}


#endif // TWL_FILES_MAP_MAP_H
