//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_DATAFILE_BASE_H
#define TWL_FILES_DATAFILE_BASE_H


#include "file_base.h"

#include <mlk/types/types.h>

#include <cstdint>
#include <fstream>


namespace twl
{
	namespace internal
	{
		class datafile_base : public file_base
		{
		protected:
			std::fstream m_filestre;

		public:
			template<typename T>
			datafile_base(const T& file, std::ios::openmode openmodes) :
				file_base{file},
				m_filestre{m_path, openmodes}
			{ }

			~datafile_base()
			{m_filestre.close();}


			std::int64_t read(std::int64_t from, std::int64_t to, mlk::data_packet& data_buf)
			{
				if(!this->valid())
					return -1;

				std::int64_t len{to - from};
				std::int64_t was_pos{this->pos()};

				m_filestre.seekg(from);
				m_filestre.read(reinterpret_cast<char*>(&data_buf[0]), len);
				return this->pos() - was_pos;
			}

			std::int64_t read(std::uint64_t len, void* data_buf) // TODO: maybe do this without raw pointer
			{
				if(!this->valid())
					return -1;

				std::int64_t was_pos{this->pos()};
				m_filestre.read(reinterpret_cast<char*>(data_buf), len);
				return this->pos() - was_pos;
			}

			bool valid() noexcept {return m_filestre.is_open();}
			std::int64_t pos() noexcept {return m_filestre.tellg();}
		};
	}
}


#endif // TWL_FILES_DATAFILE_BASE_H
