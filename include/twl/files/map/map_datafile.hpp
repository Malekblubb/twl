//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_H
#define TWL_FILES_MAP_DATAFILE_H


#include "map_datafile_items.hpp"

#include <mlk/filesystem/filesystem.h>
#include <mlk/log/log.h>


namespace twl
{
	class map_datafile
	{
		mlk::fs::file_handle m_file{""};
		mlk::data_packet m_raw;

		bool m_gotpath{false};

	public:
		map_datafile() = default;

		map_datafile(const std::string& path) :
			m_file{path},
			m_gotpath{true}
		{ }

		bool open()
		{
			if(!m_gotpath)
			{
				mlk::lerr()["twl::map_datafile"] << "got no path, can't open";
				return false;
			}
			return this->parse();
		}

		bool open(const std::string& path)
		{
			m_gotpath = true;
			m_file.reopen(path, std::ios::in);
			return this->parse();
		}

	private:
		bool parse()
		{
			if(!m_file.exists())
			{
				mlk::lerr()["twl::map_datafile"] << "given path does not exist, can't parse";
				return false;
			}

			m_raw = m_file.read_all();

			auto header(reinterpret_cast<internal::map_datafile_header*>(m_raw.data()));
			std::cout << header->body_size() << std::endl;

			return true;
		}
	};
}


#endif // TWL_FILES_MAP_DATAFILE_H
