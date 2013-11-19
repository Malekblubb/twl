//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_REPLY_H
#define TWL_NETWORK_SERVER_REPLY_H


#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		class server_rep
		{
			mlk::data_packet m_rep_data;

		public:
			server_rep(const mlk::data_packet& rep_data) :
				m_rep_data{rep_data}
			{ }

			const mlk::data_packet& reply_data() const noexcept {return m_rep_data;}

			bool operator==(const server_rep& o) const noexcept
			{return m_rep_data == o.m_rep_data;}

			bool operator!=(const server_rep& o) const noexcept
			{return m_rep_data != o.m_rep_data;}
		};
	}
}


#endif // TWL_NETWORK_SERVER_REPLY_H
