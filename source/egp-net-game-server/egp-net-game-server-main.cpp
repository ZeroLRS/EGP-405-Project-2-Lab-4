#include "DemoServer.h"
#include "ServerState.h"
#include <iostream>

bool initServer(DemoServer* _server)
{
	int numClients;

	std::cout << "Enter maximum number of clients: \n";

	std::cin >> numClients;

	if (!_server->StartupNetworking(false, numClients, 0, true))
	{
		return false;
	}

	return true;
}

int main(int const argc, char const *const *const argv)
{
	DemoServer* server = new DemoServer();
	ServerState* state = server->getCurrentState();

	if (!initServer(server))
	{
		return -1;
	}

	while (1)
	{
		server->update();
	}

	return 0;
}