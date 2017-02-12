//
// Copyright (c) 2013-2017 Christoph Malek
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
		std::vector<internal::quad> m_quads;
		std::string m_name;

		map_layer_quads(const internal::map_datafile_layer_quads* qds,
						const std::vector<mlk::data_packet>& uncompressed_data,
						const std::vector<map_image>& images)
			: internal::basic_map_layer{map_constants::layer_type::quads},
			  m_image{qds->image >= 0 ? &images.at(qds->image) : nullptr},
			  m_quads(qds->num_quads),
			  m_name{qds->version > 1 ? map_constants::ints_to_str(qds->name, 3)
									  : "Quads"}
		{
			if((qds->data >= 0) && (uncompressed_data[qds->data].size() ==
									sizeof(internal::quad) * qds->num_quads))
			{
				// add the quads
				mlk::data_packet tmp(sizeof(internal::quad));
				for(auto i(0); i < uncompressed_data[qds->data].size();
					i += sizeof(internal::quad))
				{
					tmp = {std::begin(uncompressed_data[qds->data]) + i,
						   std::end(uncompressed_data[qds->data])};
					m_quads[i / sizeof(internal::quad)] =
						*reinterpret_cast<const internal::quad*>(tmp.data());
				}
			}
		}

	public:
		map_layer_quads() = default;

		const auto* image() const noexcept { return m_image; }

		auto has_image() const noexcept { return m_image != nullptr; }

		const auto& name() const noexcept { return m_name; }

		const auto& quads() const noexcept { return m_quads; }
	};
}

#endif// TWL_FILES_MAP_MAP_LAYER_QUADS_H
