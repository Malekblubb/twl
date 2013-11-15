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

#include <mlk/log/log.h>

#include <map>
#include <string>
#include <vector>


namespace twl
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
		std::map<std::string, map_itm::map_image> m_images;


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
			auto groups(m_datafile.items_of_type<item_type::group>());
			auto layers(m_datafile.items_of_type<item_type::layer>());
			int layer_start{m_datafile.find_item<item_type::layer>().first};



			for(auto& a : groups)
			{
				// construct new group
				internal::map_datafile_group basic_group{a};
				auto ext_group(internal::make_group(basic_group));
				ext_group.set_order(this->num_groups()); // set the order manually


				// TODO: maybe do the layers better one day
				for(int i{0}; i < basic_group.num_layers(); ++i)
				{
					int layer_index{basic_group.start_layer() + i};
					internal::basic_map_datafile_layer basic_layer{layers[layer_index]};

					std::cout << basic_layer.type() << std::endl;

					if(basic_layer.type() == mlk::enum_utl::to_int(layer_type::tiles))
					{
						internal::map_datafile_layer<layer_type::tiles> tmp_basic{layers[layer_index]};
						auto ext_layer = internal::make_layer(tmp_basic);
						ext_layer.set_group_index(this->num_groups());
						ext_layer.set_order(i);
						ext_group.add_layer(ext_layer);
					}
					else if(basic_layer.type() == mlk::enum_utl::to_int(layer_type::quads))
					{
						internal::map_datafile_layer<layer_type::quads> tmp_basic{layers[layer_index]};
						auto ext_layer = internal::make_layer(tmp_basic);
						ext_layer.set_group_index(this->num_groups());
						ext_layer.set_order(i);
						ext_group.add_layer(ext_layer);
					}
					else
					{
						mlk::lerr() << "invalid layer, aborting";
						m_valid = false;
						return;
					}
				}

				this->add_group(ext_group); // save this group
			}


			m_valid = true;
		}


	public:
		void add_group(const map_itm::map_group& group) noexcept
		{m_groups.push_back(group);}

		const map_itm::map_group& group_at(int index) const noexcept
		{return m_groups.at(index);} // TODO

		std::size_t num_groups() const noexcept
		{return m_groups.size();}

		bool valid() const noexcept {return m_valid;}
	};
}



#endif // TWL_FILES_MAP_EXTENDED_MAP_H
