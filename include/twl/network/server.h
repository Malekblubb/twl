//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_H
#define TWL_NETWORK_SERVER_H


#include "server_base.h"
#include "server_request.h"

#include <mlk/tools/random_utl.h>


namespace twl
{
	class server : public internal::server_base
	{
		unsigned char m_token{mlk::rnd<unsigned char>(0, 9)}; // get random token

	public:
		server() :
			internal::server_base{mlk::ntw::packet{internal::server_req<internal::req_type::info>{}.request_data()}.add({m_token})}
		{ }

		void get_info()
		{
			this->send_reuest();

		}

	private:
		void make_entry(const mlk::data_packet &data) override
		{
			std::cout << "got entry" << std::endl;
		}
	};
}


#endif // TWL_NETWORK_SERVER_H
