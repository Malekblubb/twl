//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_READER_H
#define TWL_FILES_MAP_DATAFILE_READER_H


#include "datafile_base.h"
#include "map_datafile_body.h"
#include "map_datafile_items.h"

#include <mlk/log/log.h>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			class map_datafile_reader
			{
				datafile_base m_base_impl;

				map_datafile_header m_header{{0}};
				map_datafile_body m_body;
				bool m_valid{false};

			public:
				template<typename T>
				map_datafile_reader(const T& file) :
					m_base_impl{file, std::ios::in}
				{ }

				bool open()
				{
					// nothing to do here
					return m_base_impl.valid();
				}

				bool parse_file()
				{
					this->parse_header();

					if(!m_valid)
						return false;

					this->parse_body();
					return true; // TODO: add body checking here
				}

			private:
				void parse_header()
				{
					this->read(m_header);

					if(!m_header.valid())
					{
						m_valid = false;
						mlk::lerr() << "map unsupported, invalid header";
						return;
					}
				}

				void parse_body()
				{
					mlk::data_packet data(m_header.body_size());
					this->read(data);
					m_body = map_datafile_body{data, m_header};
				}

				// reader wrapper
				template<typename T>
				std::int64_t read(T& map_df_item)
				{return m_base_impl.read(sizeof(T), &map_df_item);}

				std::int64_t read(mlk::data_packet& data)
				{return m_base_impl.read(data.size(), &data[0]);}


			public:
				bool valid() const noexcept {return m_valid;}
				bool exists() const noexcept {return m_base_impl.exists();}
			};
		}
	}
}



#endif // TWL_FILES_MAP_DATAFILE_READER_H
