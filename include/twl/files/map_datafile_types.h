//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_TYPES_H
#define TWL_FILES_MAP_DATAFILE_TYPES_H


namespace twl
{
	namespace file
	{
		enum class item_type : int
		{
			version = 0,
			info,
			image,
			envelope,
			group,
			layer,
			envpoints
		};
	}
}


#endif // TWL_FILES_MAP_DATAFILE_TYPES_H
