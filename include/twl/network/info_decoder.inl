//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_INFO_DECODER_INL
#define TWL_NETWORK_INFO_DECODER_INL


#include "info_decoder.h"

#include "server_info.h"


namespace twl
{
	namespace internal
	{
		class dsi_helper
		{
			mlk::data_packet m_data;
			std::size_t m_current{0};

		public:
			dsi_helper(const mlk::data_packet& data) :
				m_data(data)
			{this->get_next(); /*goto version*/}

			std::string get_next() noexcept
			{
				if(this->valid())
				{
					std::string result;
					auto null_pos(std::find(m_data.begin() + m_current, m_data.end(), 0));
					for(auto begin(m_data.begin() + m_current); begin != null_pos; ++begin)
					{
						result += *begin;
						m_current++;
					}
					m_current++;
					return result;
				}
				return "";
			}

		private:
			bool valid() const noexcept
			{return m_data.size() != m_current;}
		};


		inline bool decode_server_info(const basic_server_entry &entry, server_info &info)
		{
			dsi_helper dsi{entry.data()}; // parser
			info.version = dsi.get_next();
			info.name = dsi.get_next();
			info.map_name = dsi.get_next();
			info.game_type = dsi.get_next();
			dsi.get_next();
			info.num_players = mlk::stl_string::to_int(dsi.get_next());
			info.max_players = mlk::stl_string::to_int(dsi.get_next());
			info.num_clients = mlk::stl_string::to_int(dsi.get_next());
			info.max_clients = mlk::stl_string::to_int(dsi.get_next());

			for(auto i(0); i < info.num_clients; ++i)
			{
				info.clients.push_back({dsi.get_next(), dsi.get_next(),
										mlk::stl_string::to_int(dsi.get_next()), mlk::stl_string::to_int(dsi.get_next()), mlk::stl_string::to_int(dsi.get_next())});
			}
			return true;
		}
	}
}



#endif // TWL_NETWORK_INFO_DECODER_INL
