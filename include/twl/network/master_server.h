//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_MASTER_SERVER_H
#define TWL_NETWORK_MASTER_SERVER_H


#include "info_decoder.h"
#include "server_base.h"
#include "server_reply.h"


namespace twl
{
	class master_server : public internal::server_base
	{
		internal::server_req<internal::req_type::list> m_list_request;
		internal::server_req<internal::req_type::count> m_count_request;
		int m_count{0};
		ip_list m_ip_list;

	public:
		master_server() :
			internal::server_base{internal::server_req<internal::req_type::count>{}.request_data()}
		{ }

		int get_count()
		{
			this->prepare_count();
			return m_count;
		}

		const ip_list& get_list()
		{
			this->prepare_list();
			return m_ip_list;
		}

	private:
		void make_entry(const internal::basic_server_entry& entry) override
		{
			if(internal::server_rep<internal::rep_type::count>{} == entry.data())
				m_count += internal::decode_count_info(entry.data());
			else if(internal::server_rep<internal::rep_type::list>{} == entry.data())
				internal::decode_list_info(entry.data(), m_ip_list);
		}

		void prepare_count() noexcept
		{
			m_count = 0;
			this->set_connection_packet(m_count_request.request_data());
			this->refresh();
		}

		void prepare_list() noexcept
		{
			m_ip_list.clear();
			this->set_connection_packet(m_list_request.request_data());
			this->refresh();
		}
	};
}


#endif // TWL_NETWORK_MASTER_SERVER_H
