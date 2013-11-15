//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_FILES_FILE_BASE_H
#define TWL_FILES_FILE_BASE_H


#include <mlk/filesystem/filesystem.h>
#include <mlk/tools/type_utl.h>

#include <string>


namespace twl
{
	namespace internal
	{
		class file_base
		{
		protected:
			std::string m_path;

		public:
			template<typename T>
			file_base(const T& file) :
				m_path{mlk::fs::as_path(file)}
			{ }

			bool exists() const noexcept {return mlk::fs::fs_handle<mlk::fs::fs_type::file>{m_path}.exists();}
		};
	}
}



#endif // TWL_FILES_FILE_BASE_H
