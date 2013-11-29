//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_NETWORK_UTL_H
#define TWL_NETWORK_NETWORK_UTL_H


#include <mlk/network/network.h>

#include <mlk/types/types.h>


namespace twl
{
	namespace internal
	{
		std::string from_binary_ip(bool ip_4, const mlk::data_packet& binary_ip)
		{
			std::vector<char> raw_resutl(INET6_ADDRSTRLEN);
			int af = ip_4 ? AF_INET : AF_INET6;
			if(inet_ntop(af, binary_ip.data(), raw_resutl.data(), raw_resutl.size()))
			{
				if(ip_4) return raw_resutl.data();
				else return {"[" + std::string{raw_resutl.data()} + "]"};
			}
			return "0.0.0.0";
		}
	}
}


#endif // TWL_NETWORK_NETWORK_UTL_H
