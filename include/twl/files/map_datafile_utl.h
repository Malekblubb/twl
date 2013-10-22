//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_UTL_H
#define TWL_FILES_MAP_DATAFILE_UTL_H


#include <mlk/containers/container_utl.h>
#include <mlk/types/types.h>

#include <cstdint>
#include <vector>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			// calc the length of the data sections from the given offsets
			// offsets must be sortet like: 0, 10, 24, 26, 30, 50
			inline auto calc_data_length(const std::vector<int>& offset_cnt, int data_area_len)
			-> std::vector<int>
			{
				std::size_t size{offset_cnt.size()};
				std::vector<int> ret_vec;

				for(int i{0}; i < size; ++i)
				{
					if(i != size - 1)
					{
						ret_vec.push_back(offset_cnt.at(i + 1) - offset_cnt.at(i));
						continue;
					}

					// last element
					ret_vec.push_back(data_area_len - offset_cnt.at(i));
				}

				return ret_vec;
			}
		}
	}
}


#endif // TWL_FILES_MAP_DATAFILE_UTL_H
