//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_LAYER_QUADS_H
#define TWL_FILES_MAP_MAP_LAYER_QUADS_H


#include "basic_map_layer.hpp"
#include "map_datafile_items.hpp"
#include "map_image.hpp"

#include <map>


namespace twl
{
	class map_layer_quads : public internal::basic_map_layer
	{
		friend class map;

		const map_image* m_image{nullptr};
		std::string m_name;

		// std::vector<quad>

		map_layer_quads(const internal::map_datafile_layer_quads* qds, const std::vector<mlk::data_packet>& uncompressed_data, const std::vector<map_image>& images) :
			internal::basic_map_layer{map_constants::layer_type::quads},
			m_image{qds->image >= 0 ? &images.at(qds->image) : nullptr}
		{ }

	public:
		map_layer_quads() = default;

		const auto* image() const noexcept
		{return m_image;}

		auto has_image() const noexcept
		{return m_image != nullptr;}
	};
}


#endif // TWL_FILES_MAP_MAP_LAYER_QUADS_H
