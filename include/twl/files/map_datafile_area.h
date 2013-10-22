//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_MAP_DATAFILE_AREA_H
#define TWL_FILES_MAP_DATAFILE_AREA_H


#include <mlk/types/types.h>


#include <functional>


namespace twl
{
	namespace file
	{
		namespace internal
		{
			template<typename T, typename E = std::vector<T>()>
			class map_datafile_area
			{
				std::vector<T> m_items;
				mlk::data_packet m_data;
				std::function<E> m_process_fnc;


			public:
				void on_process_data(mlk::data_packet& data, std::function<E> fnc)
				{
					m_data = data; // take the reference
					m_process_fnc = fnc;
					this->process_data();
				}

				void process_data()
				{
					m_process_fnc();
				}
			};
		}
	}
}


#endif // TWL_FILES_MAP_DATAFILE_AREA_H
