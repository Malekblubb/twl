//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_DATAFILE_MANAGER_H
#define TWL_FILES_MAP_MAP_DATAFILE_MANAGER_H

#include "map_datafile_items.hpp"
#include "map_datafile_parser.hpp"

#include <mlk/filesystem/filesystem.h>
#include <mlk/log/log.h>

namespace twl
{
	namespace internal
	{
		class map_datafile_manager
		{
			mlk::fs::file_handle m_file{""};
			mlk::data_packet m_raw;
			map_datafile_parser m_parser;

			bool m_gotpath{false};

		public:
			map_datafile_manager() = default;

			map_datafile_manager(const std::string& path)
				: m_file{path}, m_gotpath{true}
			{
			}

			bool open()
			{
				if(!m_gotpath) {
					mlk::lerr()["twl::map_datafile"]
						<< "got no path, can't open";
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

			void close()
			{
				mlk::lout("twl::map_datafile_manager") << "closing map";
				m_parser.clear();
			}

			const auto& parser() const noexcept { return m_parser; }

		private:
			bool parse()
			{
				if(!m_file.exists()) {
					mlk::lerr()["twl::map_datafile"]
						<< "given path does not exist, can't parse";
					return false;
				}

				// read data
				m_raw = m_file.read_all();

				// start parse
				m_parser.start_parse(&m_raw);

				// free raw data
				mlk::cnt::free_vec(m_raw);

				return true;
			}
		};
	}
}

#endif// TWL_FILES_MAP_MAP_DATAFILE_MANAGER_H
