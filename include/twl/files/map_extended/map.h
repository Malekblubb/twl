//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_EXTENDED_MAP_H
#define TWL_FILES_MAP_EXTENDED_MAP_H


#include "map_utl.h"
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
				auto groups = m_datafile.items_of_type<item_type::group>();

				for(auto& a : groups)
				{
					// construct new group
					internal::map_datafile_group basic_group{a};
					map_itm::map_group ext_group{map_utl::internal::make_group(basic_group)};
					ext_group.set_order(m_groups.size()); // set the order manually
					m_groups.push_back(ext_group); // save this group

//					std::cout << m_groups.back().clip_x() << std::endl;
				}


				m_valid = true;
			}


		public:
			bool valid() const noexcept {return m_valid;}
		};
	}
}



#endif // TWL_FILES_MAP_EXTENDED_MAP_H
