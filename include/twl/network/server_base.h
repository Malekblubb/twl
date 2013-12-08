//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_SERVER_BASE_H
#define TWL_NETWORK_SERVER_BASE_H


#include "basic_connection.h"
#include "basic_server_entry.h"


namespace twl
{
	using ip_list = std::vector<mlk::ntw::ip_address>;

	namespace internal
	{
		class server_base
		{
			static constexpr mlk::llong m_min_recv_time{1}, m_max_recv_time{300};

			basic_connection m_connection;
			mlk::slot<const mlk::data_packet&, const mlk::ntw::ip_address&> m_on_recv;

		protected:
			std::vector<internal::basic_server_entry> m_servers;

		public:
			server_base(const mlk::ntw::packet& packet) :
				m_connection{packet}
			{
				m_on_recv += [this](const mlk::data_packet& data, const mlk::ntw::ip_address& address)
				{this->on_received(data, address);};
				mlk::link_signal(m_connection.m_received, m_on_recv);
			}

			virtual ~server_base() = default;

			void add(const mlk::ntw::ip_address& address)
			{this->add_impl(address);}

			auto num_servers() const noexcept
			-> decltype(m_servers.size())
			{return m_servers.size();}

		protected:
			void set_connection_packet(const mlk::ntw::packet& packet)
			{m_connection.set_packet(packet);}

			void refresh()
			{
				auto count(0);
				for(auto& a : m_servers)
				{
					if(count >= 200)
						m_connection.recv<m_min_recv_time>();

					m_connection.send(a.address());
					a.on_send();

					++count;
				}
				m_connection.recv<m_max_recv_time>();
			}

			bool server_exists(const mlk::ntw::ip_address& address) const noexcept
			{
				return mlk::cnt::find_in_if(
				[&](const internal::basic_server_entry& e)
				{return e.address() == address;}, m_servers) != m_servers.end();
			}

		private:
			void add_impl(const mlk::ntw::ip_address& address) noexcept
			{
				if(this->server_exists(address))
					return;
				m_servers.push_back({address});
			}

			void on_received(const mlk::data_packet& data, const mlk::ntw::ip_address& address)
			{
				// find the server in the list
				for(auto& a : m_servers)
					if(a.address() == address)
					{
						a.on_recv();
						a.data() = data;

						// call custom make entry function
						this->make_entry(a);
						return;
					}
			}

			virtual void make_entry(const internal::basic_server_entry& entry) = 0;
		};
	}
}


#endif // TWL_NETWORK_SERVER_BASE_H
