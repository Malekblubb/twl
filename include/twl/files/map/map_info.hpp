//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_INFO_H
#define TWL_FILES_MAP_MAP_INFO_H


#include "map_datafile_items.hpp"

#include <string>


namespace twl
{
	class map_info
	{
		friend class map;

		std::string m_author;
		std::string m_mapversion;
		std::string m_credits;
		std::string m_license;

		map_info(const internal::map_datafile_info* info, const std::vector<mlk::data_packet>& uncompressed_data) :
			m_author{info->author >= 0 ? reinterpret_cast<const char*>(uncompressed_data[info->author].data()) : ""},
			m_mapversion{info->map_version >= 0 ? reinterpret_cast<const char*>(uncompressed_data[info->map_version].data()) : ""},
			m_credits{info->credits >= 0 ? reinterpret_cast<const char*>(uncompressed_data[info->credits].data()) : ""},
			m_license{info->license >= 0 ? reinterpret_cast<const char*>(uncompressed_data[info->license].data()) : ""}
		{ }

	public:
		map_info() = default;

		const auto& author() const noexcept
		{return m_author;}

		const auto& mapversion() const noexcept
		{return m_mapversion;}

		const auto& credits() const noexcept
		{return m_credits;}

		const auto& license() const noexcept
		{return m_license;}
	};
}


#endif // TWL_FILES_MAP_MAP_INFO_H