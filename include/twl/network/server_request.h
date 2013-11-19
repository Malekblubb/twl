//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_REQUEST_H
#define TWL_NETWORK_SERVER_REQUEST_H


#include <mlk/types/types.h>

#include <algorithm>


namespace twl
{
	namespace internal
	{
		enum class req_type : int
		{list, count, info};

		class server_req_base
		{
			// connless bytes(first 6) are directly here
			mlk::data_packet m_req_data{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

		public:
			server_req_base(const mlk::data_packet& req_data)
			{m_req_data.insert(m_req_data.end(), req_data.begin(), req_data.end());}

			const mlk::data_packet& request_data() const noexcept {return m_req_data;}
		};

		template<req_type type>
		struct server_req : public server_req_base
		{server_req() = delete;};

		// master requests
		template<>
		struct server_req<req_type::list> : public server_req_base
		{
			server_req() :
				server_req_base{{'r', 'e', 'q', '2'}}
			{ }
		};

		template<>
		struct server_req<req_type::count> : public server_req_base
		{
			server_req() :
				server_req_base{{'c', 'o', 'u', '2'}}
			{ }
		};

		// server requests
		template<>
		struct server_req<req_type::info> : public server_req_base
		{
			server_req() :
				server_req_base{{'g', 'i', 'e', '3'}}
			{ }
		};
	}
}


#endif // TWL_NETWORK_SERVER_REQUEST_H
