//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
#define TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H


#include "item_base.h"

#include <twl/files/map_datafile/map_datafile_types.h>

#include <mlk/tools/enum_utl.h>


namespace twl
{
	namespace map_itm
	{
		using layer_type = file::layer_type;

		namespace internal
		{
			class map_layer_base
			{
				int m_type{0};
				int m_flags{0};

			public:
				map_layer_base(int type, int flags) :
					m_type{type},
					m_flags{flags}
				{ }

			};
		}


		template<layer_type type>
		class map_layer{public: map_layer() = delete;};


		template<>
		class map_layer<layer_type::tiles> : public internal::map_layer_base
		{

		public:
			map_layer(int flags = 0) :
				internal::map_layer_base{mlk::enum_utl::to_int(layer_type::tiles), flags}
			{ }
		};


		template<>
		class map_layer<layer_type::quads> : public internal::map_layer_base
		{

		public:
			map_layer(int flags = 0) :
				internal::map_layer_base{mlk::enum_utl::to_int(layer_type::quads), flags}
			{ }
		};



//		template<typename T, typename E>
//		E layer_cast(const layer)
//		{
////			return
//		}
	}
}


#endif // TWL_FILES_MAP_EXTENDED_ITEMS_LAYER_H
