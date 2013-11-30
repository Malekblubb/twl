//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_CLIENT_INFO_H
#define TWL_NETWORK_CLIENT_INFO_H


#include <string>


namespace twl
{
	struct client_info
	{
		std::string name;
		std::string clan;
		int country;
		int score;
		int is_player;
	};
}



#endif // TWL_NETWORK_CLIENT_INFO_H
