//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_MAP_DATAFILE_PARSER_H
#define TWL_FILES_MAP_MAP_DATAFILE_PARSER_H


#include "map_datafile.hpp"

#include <mlk/compression/compression.h>
#include <mlk/containers/container_utl.h>


namespace twl
{
	namespace internal
	{
		class map_datafile_parser
		{
			// input
			const mlk::data_packet* m_raw{nullptr};

			// output
			map_datafile m_result;

		public:
			void start_parse(const mlk::data_packet* raw)
			{
				m_raw = raw;
				this->parse();
			}

			const map_datafile& result() const noexcept
			{return m_result;}

		private:
			void parse()
			{
				if(m_raw == nullptr)
					return;

				// cast header
				auto* header(reinterpret_cast<const map_datafile_header*>(m_raw->data()));

				// skip item types & item offsets
				mlk::st pos{sizeof(map_datafile_header) + header->num_itemtypes * sizeof(map_datafile_iteminfo) + header->num_items * 4};


				// data offsets and uncompressed sizes
				std::vector<int> data_offsets(header->num_rawdata), uncompressed_sizes(header->num_rawdata);

				for(auto i(0); i < header->num_rawdata; ++i)
					data_offsets[i] = *reinterpret_cast<int*>(mlk::data_packet{std::begin(*m_raw) + pos + i * 4, std::end(*m_raw)}.data());
				pos += 4 * header->num_rawdata;

				for(auto i(0); i < header->num_rawdata; ++i)
					uncompressed_sizes[i] = *reinterpret_cast<int*>(mlk::data_packet{std::begin(*m_raw) + pos + i * 4, std::end(*m_raw)}.data());
				pos += 4 * header->num_rawdata;


				// parse the items
				for(auto i(0); i < header->num_items; ++i)
				{
					mlk::data_packet tmp{std::begin(*m_raw) + pos, std::end(*m_raw)};
					auto* iteminfo(reinterpret_cast<basic_map_datafile_item*>(tmp.data()));

					// build the item
					m_result.add_item({(iteminfo->type_and_id >> 16) & 0xff, // type
									   (iteminfo->type_and_id >> 24) & 0xff, // id
									   {std::begin(tmp) + sizeof(basic_map_datafile_item),
										std::begin(tmp) + sizeof(basic_map_datafile_item) + iteminfo->length}}); // data

					// move forward
					pos += sizeof(basic_map_datafile_item) + iteminfo->length;
				}


				// parse data, decompress it directly
				std::vector<mlk::data_packet> uncompressed_data(header->num_rawdata);
				for(auto i(0); i < header->num_rawdata; ++i)
				{
					if(i != header->num_rawdata - 1)
					{
						mlk::cmprs::compressor_zlib cmprs{{std::begin(*m_raw) + pos, std::begin(*m_raw) + pos + (data_offsets[i + 1] - data_offsets[i])}};
						cmprs.unpack(uncompressed_sizes[i]);
						if(cmprs.is_valid())
							uncompressed_data[i] = cmprs.get();

						pos += data_offsets[i + 1] - data_offsets[i];
						continue;
					}

					mlk::cmprs::compressor_zlib cmprs{{std::begin(*m_raw) + pos, std::begin(*m_raw) + pos + header->data_area_size - data_offsets[i]}};
					cmprs.unpack(uncompressed_sizes[i]);
					if(cmprs.is_valid())
						uncompressed_data[i] = cmprs.get();

					pos += header->data_area_size - data_offsets[i];
				}

				// move the data to result
				m_result.add_uncompressed_data(uncompressed_data);
			}
		};
	}
}


#endif // TWL_FILES_MAP_MAP_DATAFILE_PARSER_H

