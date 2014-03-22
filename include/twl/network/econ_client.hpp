//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_ECON_CLIENT_HPP
#define TWL_NETWORK_ECON_CLIENT_HPP


#include "econ_parser.hpp"
#include "ntw_constants.hpp"

#include <mlk/network/network.h>
#include <mlk/signals_slots/slot.h>
#include <mlk/time/simple_timer.h>
#include <mlk/tools/stl_string_utl.h>

#include <deque>


namespace twl
{
	class econ_client
	{
		// connection
		mlk::ntw::telnet_client<false> m_telnet;
		mlk::data_packet m_recv_data;

		// on next update
		mlk::ntw::ip_address m_next_addr;
		std::string m_next_pass;
		std::deque<econ_command> m_cmd_queue;

		// connect timeout
		mlk::tm::simple_timer m_timeouttimer{internal::ntw_constants::econ_timeout()};

		// log
		std::string m_logstr;

		bool m_running{false}, m_new_connection{true};
		bool m_connected{false}, m_logged{false};
		bool m_need_connect{false}, m_need_send_pass{false};

	public:
		// slots
		mlk::slot<> on_connection;
		mlk::slot<> on_connection_lost;
		mlk::slot<> on_connection_timeout;
		mlk::slot<> on_login;
		mlk::slot<const econ_player_infos&> on_playerinfo;
		mlk::slot<const std::string&> on_log_added;

		econ_client() :
			m_recv_data(internal::ntw_constants::max_datasize())
		{ }

		econ_client(const mlk::ntw::ip_address& addr) :
			econ_client{}
		{this->connect(addr);}

		void update()
		{
			if(!m_running)
				return;

			// recv data
			this->recv();

			// process cmd queue
			for(std::size_t i{0}; i < m_cmd_queue.size(); ++i)
			{
				if(this->send_command_impl(m_cmd_queue.front()))
					m_cmd_queue.pop_front();
			}

			if(m_need_connect)
			{
				// try connect
				this->connect_impl();

				if(m_timeouttimer.timed_out())
				{
					this->reset();
					this->on_connection_timeout();
				}
			}

			// send pass if needed
			if(m_need_send_pass && m_connected)
			{
				this->send_command_impl(m_next_pass);
				m_need_send_pass = false;
			}
		}


		void connect(const mlk::ntw::ip_address& addr) noexcept
		{
			m_next_addr = addr;
			m_need_connect = true;
			m_running = true;
		}

		void login(const std::string& pass) noexcept
		{
			m_next_pass = pass;
			m_need_send_pass = true;
			m_running = true;
		}

		void request_playerinfo()
		{this->send_command("status");}

		void send_command(const econ_command& cmd)
		{m_cmd_queue.push_back(cmd);}

		bool connected() const noexcept
		{return m_connected;}

		bool logged_in() const noexcept
		{return m_logged;}

		const mlk::ntw::ip_address& address() const noexcept
		{return m_telnet.address();}

		const std::string& log() const
		{return m_logstr;}

	private:
		void reset()
		{
			m_running = false;
			m_new_connection = true;
			m_connected = false;
			m_logged = false;
			m_need_connect = false;
			m_need_send_pass = false;
		}

		void recv()
		{
			m_recv_data.clear();
			auto ret(m_telnet.recv_line(m_recv_data, internal::ntw_constants::max_datasize()));
			m_recv_data.erase(std::begin(m_recv_data) + ret, std::end(m_recv_data));

			// connection lost
			if(ret == 0)
			{
				m_connected = false;
				m_logged = false;
				m_need_send_pass = false;
				this->reset();
				this->on_connection_lost();
			}

			// recved data, still connected
			else if(ret > 0)
			{
				internal::econ_parser parser{m_recv_data};
				if(parser.login_reply())
				{
					m_need_send_pass = false;
					m_logged = true;
					this->on_login();
				}
				else if(parser.status_reply())
					this->on_playerinfo(parser.get_status_reply());

				// add log
				this->add_log();
			}
		}

		bool connect_impl()
		{
			if(m_new_connection)
			{
				m_new_connection = false;
				m_timeouttimer.run();
				m_telnet.disconnect();
			}

			m_connected = m_telnet.connect(m_next_addr);
			m_need_connect = !m_connected;
			return m_connected;
		}

		bool send_command_impl(const econ_command& cmd)
		{
			if(!m_running || !m_connected)
				return false;

			auto data(mlk::stl_string::to_data_packet(cmd));
			m_telnet.send_line(data);
			return true;
		}

		void add_log()
		{
			// delete the telnet characters at the back
			std::string str{std::begin(m_recv_data), std::end(m_recv_data)};
			mlk::stl_string::erase_all(0x00, str);
			m_logstr += str;
			this->on_log_added(str);
		}
	};
}


#endif // TWL_NETWORK_ECON_CLIENT_HPP
