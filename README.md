Twlib
=====


###Network
Get the info from a teeworlds server:
```cpp
twl::server my_server{{"my_host_name_or_ip.com", port}};
auto info(my_server.get_info());

if(info.is_valid())
{
	std::cout << "name: " << info.name << std::endl;
	std::cout << "gametype: " << info.game_type << std::endl;
	std::cout << "map_name: " << info.map_name << std::endl;
	std::cout << "version: " << info.version << std::endl;
	// ... more available (include/twl/network/server_info.h)
}
```

Masterserver request:
```cpp
twl::master_server master;
master.add({"master1.teeworlds.com:8300"});
master.add({"master2.teeworlds.com:8300"});
auto count(master.get_count()); // get number of servers that are registered on the added masters
auto registered_ips(master.get_list()); // get registered server ips

for(auto& a : registered_ips)
{
	// iterate through the ips
	std::cout << "address: " << a << std::endl;
	// ... do some stuff
}
```

Get the info from multiple servers:
```cpp
twl::multi_server my_servers;
my_servers.add({server1.com:port});
my_servers.add({server2.com:port});
// ...

auto infos(my_servers.get_info());
for(auto& a : infos)
{
	// iterate through the infos
	std::cout << "name: " << a.name << std::endl;
	// ...
}
```
