//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_REQUESTS_HPP
#define TWL_NETWORK_REQUESTS_HPP


#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		enum class server_request : char
		{
			game_get_info,

			master_get_list,
			master_get_count
		};

		class request_base
		{
			mlk::data_packet m_data;

		public:
			request_base(mlk::data_packet&& data) :
				m_data{std::move(data)}
			{ }

			const mlk::data_packet& operator()() const noexcept
			{return m_data;}
		};

		template<server_request>
		struct request;

		template<>
		struct request<server_request::game_get_info> : public request_base
		{
			request() :
				request_base{{0xff, 0xff, 0xff, 0xff, 'g', 'i', 'e', '3'}}
			{ }
		};

		template<>
		struct request<server_request::master_get_list> : public request_base
		{
			request() :
				request_base{{0xff, 0xff, 0xff, 0xff, 'r', 'e', 'g', '2'}}
			{ }
		};

		template<>
		struct request<server_request::master_get_count> : public request_base
		{
			request() :
				request_base{{0xff, 0xff, 0xff, 0xff, 'c', 'o', 'u', '2'}}
			{ }
		};
	}
}


#endif // TWL_NETWORK_REQUESTS_HPP
