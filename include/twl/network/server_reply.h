//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_REPLY_H
#define TWL_NETWORK_SERVER_REPLY_H


#include <mlk/types/types.h>

#include <algorithm>


namespace twl
{
	namespace internal
	{
		enum class rep_type : int
		{list, count, info};

		class server_rep_base
		{
			// connless bytes(first 6) are directly here
			mlk::data_packet m_rep_data{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

		public:
			server_rep_base(const mlk::data_packet& rep_data)
			{m_rep_data.insert(m_rep_data.end(), rep_data.begin(), rep_data.end());}

			bool operator==(const mlk::data_packet& data)
			{return std::equal(m_rep_data.begin(), m_rep_data.end(), data.begin());}
		};

		template<rep_type type>
		struct server_rep : public server_rep_base
		{server_rep() = delete;};

		// master replies
		template<>
		struct server_rep<rep_type::list> : public server_rep_base
		{
			server_rep() :
				server_rep_base{{'l', 'i', 's', '2'}}
			{ }
		};

		template<>
		struct server_rep<rep_type::count> : public server_rep_base
		{
			server_rep() :
				server_rep_base{{'s', 'i', 'z', '2'}}
			{ }
		};

		// server replies
		template<>
		struct server_rep<rep_type::info> : public server_rep_base
		{
			server_rep() :
				server_rep_base{{'i', 'n', 'f', '3'}}
			{ }
		};
	}
}


#endif // TWL_NETWORK_SERVER_REPLY_H
