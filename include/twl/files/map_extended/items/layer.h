//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
#define TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H


#include "item_base.h"


namespace twl
{
	namespace map_itm
	{
		namespace internal
		{
			class map_layer_base
			{

			public:

			};
		}


		class map_tiles_layer :
				public internal::map_layer_base,
				public internal::map_item_base
		{

		public:

		};

		class map_quads_layer :
				public internal::map_layer_base,
				public internal::map_item_base
		{

		public:

		};
	}
}


#endif // TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
