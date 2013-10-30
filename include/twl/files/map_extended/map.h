//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_MAP_H
#define TWL_FILES_MAP_EXTENDED_MAP_H


#include "items/items.h"

#include <twl/files/map_datafile/map_datafile.h>
#include <twl/files/map_datafile/map_datafile_types.h>


namespace twl
{
	namespace file
	{
		class map
		{
			// uderlaying datafile
			internal::map_datafile m_datafile{""};

			bool m_valid{false};

			// items
			// groups
			std::vector<map_itm::map_group> m_groups;

			// images



		public:
			// provide an empty ctor
			map() = default;

			template<typename T>
			map(const T& file) :
				m_datafile{file}
			{
				if(m_datafile.valid())
					this->process_datafile();
			}

		private:
			void process_datafile()
			{
//				auto a = m_datafile.items_of_type<item_type::layer>();
				auto groups = m_datafile.items_of_type<item_type::group>();
				for(auto& a : groups)
				{
					internal::map_datafile_group basic_group{a};
					map_itm::map_group ext_group;
				}


				m_valid = true;
			}


		public:
			bool valid() const noexcept {return m_valid;}
		};
	}
}



#endif // TWL_FILES_MAP_EXTENDED_MAP_H
