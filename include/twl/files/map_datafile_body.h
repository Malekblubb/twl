//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_BODY_H
#define TWL_FILES_MAP_DATAFILE_BODY_H


#include "map_datafile_area.h"
#include "map_datafile_items.h"
#include "map_datafile_utl.h"

#include <mlk/containers/container_utl.h>
#include <mlk/types/types.h>

#include <vector>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			class map_datafile_body
			{
				mlk::data_packet m_data;

				map_datafile_header m_header{{0}};
				map_datafile_area<map_datafile_iteminfo> m_iteminfo_area;
				map_datafile_area<int> m_item_offset_area;
				map_datafile_area<int> m_data_offset_area;
				map_datafile_area<int> m_ucmp_datasize_area;
				map_datafile_area<map_datafile_item> m_item_area;
				map_datafile_area<mlk::data_packet> m_data_area;

			public:
				map_datafile_body() = default;

				map_datafile_body(const mlk::data_packet& data, const map_datafile_header& header) :
					m_data(data),
					m_header(header)
				{this->process_data();}


				// process the input data
				void process_data()
				{
					int loops{this->iteminfo_area_size()};

					m_iteminfo_area.on_process_data(m_data,
					[&]
					{
						std::vector<map_datafile_iteminfo> result;
						for(int i{0}; i < loops; i += sizeof(map_datafile_iteminfo))
							result.push_back(map_datafile_iteminfo{mlk::cnt::make_int(i, m_data),
																   mlk::cnt::make_int(i+4, m_data),
																   mlk::cnt::make_int(i+8, m_data)});

						return result;
					});

					loops += this->itemoffset_area_size();

					m_item_offset_area.on_process_data(m_data,
					[&]
					{
						std::vector<int> result;
						for(int i{this->iteminfo_area_size()}; i < loops; i += sizeof(int))
							result.push_back(mlk::cnt::make_int(i, m_data));

						return result;
					});

					loops += this->dataoffset_area_size();

					m_data_offset_area.on_process_data(m_data,
					[&]
					{
						std::vector<int> result;
						for(int i{this->iteminfo_area_size() + this->itemoffset_area_size()}; i < loops; i += sizeof(int))
							result.push_back(mlk::cnt::make_int(i, m_data));

						return result;
					});

					loops += this->ucmpdata_area_size();

					m_ucmp_datasize_area.on_process_data(m_data,
					[&]
					{
						std::vector<int> result;
						for(int i{this->dataoffset_area_size() + this->iteminfo_area_size() + this->itemoffset_area_size()}; i < loops; i += sizeof(int))
							result.push_back(mlk::cnt::make_int(i, m_data));

						return result;
					});

					loops += this->items_area_size();

					m_item_area.on_process_data(m_data,
					[&]
					{
						std::vector<map_datafile_item> result;
						int i{this->ucmpdata_area_size() + this->dataoffset_area_size() + this->iteminfo_area_size() + this->itemoffset_area_size()};
						for(; i < loops;)
						{
							int itemsize{ mlk::cnt::make_int(i+4, m_data)};
							result.push_back(map_datafile_item{mlk::cnt::make_int(i, m_data), itemsize, mlk::cnt::cut_vec(i+8, i+8+itemsize, m_data)});
							i += (2 * sizeof(int)) + itemsize;
						}

						return result;
					});

					loops += this->data_area_size();

					m_data_area.on_process_data(m_data,
					[&]
					{
						std::vector<mlk::data_packet> result;
						std::vector<int> data_lengths{calc_data_length(m_data_offset_area.data(), this->data_area_size())};
						int i{this->items_area_size() + this->ucmpdata_area_size() + this->dataoffset_area_size() + this->iteminfo_area_size() + this->itemoffset_area_size()};

						for(int data_lengths_index{0}; i < loops; ++data_lengths_index)
						{
							result.push_back(mlk::cnt::cut_vec(i, i+data_lengths[data_lengths_index], m_data)); // TODO: this item is one byte larger because of cut_vec
							i += data_lengths[data_lengths_index];
						}

						return result;
					});
				}

				int size() const noexcept
				{return m_header.body_size();}

			private:
				int iteminfo_area_size() const noexcept
				{return m_header.m_num_itemtypes * 12;}

				int itemoffset_area_size() const noexcept
				{return m_header.m_num_items * 4;}

				int dataoffset_area_size() const noexcept
				{return m_header.m_num_rawdata * 4;}

				int ucmpdata_area_size() const noexcept
				{return m_header.m_num_rawdata * 4;}

				int items_area_size() const noexcept
				{return m_header.m_item_area_size;}

				int data_area_size() const noexcept
				{return m_header.m_data_area_size;}
			};
		}
	}
}


#endif // TWL_FILES_MAP_DATAFILE_BODY_H
