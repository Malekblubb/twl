//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_READER_H
#define TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_READER_H


#include "map_datafile_body.h"
#include "map_datafile_items.h"

#include <twl/files/datafile_base.h>

#include <mlk/compression/compression.h>
#include <mlk/log/log.h>

#include <map>


namespace twl
{
	namespace internal
	{
		class map_datafile_reader
		{
			datafile_base m_base_impl;

			map_datafile_header m_header{{0}};
			map_datafile_body m_body;
			std::map<int, mlk::data_packet> m_ucmp_data;

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

			template<item_type type>
			auto find_item()
			-> std::pair<int, int>
			{return m_body.find_item<type>();}

			template<item_type type>
			auto items_of_type()
			-> std::vector<map_datafile_item>
			{return m_body.items_of_type<type>();}

			const mlk::data_packet& item_at(int index) const
			{return m_body.item_at(index);}

			const mlk::data_packet& data_at(int index)
			{
				if(m_ucmp_data.find(index) != m_ucmp_data.end()) // data is already uncompressed
					return m_ucmp_data[index];

				// need to uncompress data
				this->uncompress_data(index);
				return m_ucmp_data[index];
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
				else
					m_valid = true;
			}

			void parse_body()
			{
				mlk::data_packet data(m_header.body_size());
				this->read(data);
				m_body = map_datafile_body{data, m_header};
			}

			void uncompress_data(int index)
			{
				std::uint64_t ucmp_size{static_cast<std::uint64_t>(m_body.data_size_at(index))};
				mlk::cmprs::compressor<mlk::cmprs::cmprs_mode::zlib> cmps{m_body.data_at(index)};
				cmps.unpack(ucmp_size);
				m_ucmp_data[index] = cmps.get();
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



#endif // TWL_FILES_MAP_DATAFILE_MAP_DATAFILE_READER_H
