//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_GROUP_H
#define TWL_FILES_MAP_MAP_GROUP_H


#include "basic_map_layer.hpp"
#include "map_datafile_items.hpp"

#include <string>
#include "map_layer_tiles.hpp"


namespace twl
{
	class map_group
	{
		friend class map;

		int m_offset_x{0}, m_offset_y{0};
		int m_parallax_x{0}, m_parallax_y{0};
		bool m_use_clipping{false};
		int m_clipping_x{0}, m_clipping_y{0};
		int m_clipping_w{0}, m_clipping_h{0};

		std::vector<mlk::sptr<const internal::basic_map_layer>> m_layers;
		std::string m_name;

		map_group(const internal::map_datafile_group* grp, const std::vector<mlk::sptr<internal::basic_map_layer>>& layers) :
			m_offset_x{grp->offset_x},
			m_offset_y{grp->offset_y},
			m_parallax_x{grp->parallax_x},
			m_parallax_y{grp->parallax_y},
			m_use_clipping{static_cast<bool>(grp->use_clipping)},
			m_clipping_x{grp->clip_x},
			m_clipping_y{grp->clip_y},
			m_clipping_w{grp->clip_w},
			m_clipping_h{grp->clip_h},
			m_name{grp->version > 2 ? map_constants::ints_to_str(grp->name, 3) : "Group"}
		{
			if(layers.size() >= grp->startlayer + grp->numlayers)
				for(auto i(grp->startlayer); i < grp->startlayer + grp->numlayers; ++i)
					m_layers.push_back(layers.at(i));
		}

	public:
		map_group() = default;

		auto offset_x() const noexcept
		{return m_offset_x;}

		auto offset_y() const noexcept
		{return m_offset_y;}

		auto parallax_x() const noexcept
		{return m_parallax_x;}

		auto parallax_y() const noexcept
		{return m_parallax_y;}

		auto clipping() const noexcept
		{return m_use_clipping;}

		auto clipping_x() const noexcept
		{return m_clipping_x;}

		auto clipping_y() const noexcept
		{return m_clipping_y;}

		auto clipping_w() const noexcept
		{return m_clipping_w;}

		auto clipping_h() const noexcept
		{return m_clipping_h;}

		const auto& layers() const noexcept
		{return m_layers;}

		const auto& name() const noexcept
		{return m_name;}
	};
}


#endif // TWL_FILES_MAP_MAP_GROUP_H
