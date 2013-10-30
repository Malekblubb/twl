//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_MAP_UTL_H
#define TWL_FILES_MAP_EXTENDED_MAP_UTL_H


#include "items/group.h"

#include <twl/files/map_datafile/map_datafile_items.h>


namespace twl
{
	namespace map_utl
	{
		namespace internal
		{
			// helper function to make a extended group out of a datafile_group
			// i don't want this as constructor in map_itm::map_group
			map_itm::map_group make_group(const file::internal::map_datafile_group& group)
			{
				map_itm::map_group result;
				result.set_clipping(group.clipping());
				result.set_clip_h(group.clip_h()); result.set_clip_w(group.clip_w());
				result.set_clip_x(group.clip_x()); result.set_clip_y(group.clip_y());
				result.set_order(-1);
				result.set_para_x(group.para_x()); result.set_para_y(group.para_y());
				result.set_pos_x(group.offset_x()); result.set_pos_y(group.offset_y()); // TODO: check this
				return result;
			}
		}
	}
}


#endif // TWL_FILES_MAP_EXTENDED_MAP_UTL_H
