Twlib
=====

###Network
Get info from a teeworlds server:
```cpp
twl::game_server my_server;
bool finished{false};

// add a server
my_server.add_server({"37.221.194.71:8000"});

// request info from that server
my_server.request_info();

// connect the finished-'signal'
my_server.on_finish = [&finished]{finished = true;};

// update the connection
while(!finished)
	my_server.update();

// get the info vector
auto infos(my_server.get_infos());

// iterate trough the infos
for(auto& a : infos)
	std::cout << a.name() << std::endl;
```
  
  
Process all servers stored by the masters:
```cpp
twl::master_server masters;
bool masters_finished{false};

// add masters
masters.add_master({"master1.teeworlds.com:8300"});
masters.add_master({"master2.teeworlds.com:8300"});

// request list
masters.request_list();

// connect the finished-'signal'
masters.on_finish = [&masters_finished]{masters_finished = true;};

// update the connection
while(!masters_finished)
	masters.update();



// masters are finished at this point
twl::game_server servers;
bool servers_finished{false};

// add the masterlist to the game_server-handle
servers.add_masterlist(masters.get_list());

// request infos
servers.request_info();

// connect the finished-'signal'
servers.on_finish = [&servers_finished]{servers_finished = true;};

// update the connection
while(!servers_finished)
	servers.update();

// get the processed server infos
auto infos(servers.get_infos());

// iterate trough the infos/servers
for(auto& a : infos)
	std::cout << a.name() << std::endl;
```