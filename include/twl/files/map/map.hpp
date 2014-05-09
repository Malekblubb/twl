//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_H
#define TWL_FILES_MAP_MAP_H


#include "map_datafile_manager.hpp"


namespace twl
{
	class map
	{
		internal::map_datafile_manager m_datafilemanager;

	public:
		map() = default;

		map(const std::string& path) :
			m_datafilemanager{path}
		{ }

		bool open()
		{
			return m_datafilemanager.open();
		}

		bool open(const std::string& path)
		{
			return m_datafilemanager.open(path);
		}
	};
}


#endif // TWL_FILES_MAP_MAP_H
