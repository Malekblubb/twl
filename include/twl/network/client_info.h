//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef TWL_NETWORK_CLIENT_INFO_H
#define TWL_NETWORK_CLIENT_INFO_H


#include <string>
#include <vector>


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

	using client_infos = std::vector<client_info>;
}



#endif // TWL_NETWORK_CLIENT_INFO_H
