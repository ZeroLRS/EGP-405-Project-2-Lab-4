#include "egp-net-framework/DemoPeerManager.h"
#include "ServerState.h"
#include <iostream>

bool initServer(DemoPeerManager* _server)
{
	int numClients;
	int port;
	std::cout << "Enter maximum number of clients: \n";

	std::cin >> numClients;

	std::cout << "Enter server port: \n";
	std::cin >> port;

	if (!_server->StartupNetworking(false, numClients, port, true))
	{
		return false;
	}

	return true;
}

int main(int const argc, char const *const *const argv)
{
	DemoPeerManager* server = DemoPeerManager::getInstance();
	ServerState* state = new ServerState();

	if (!initServer(server))
	{
		return -1;
	}

	while (1)
	{
		state->updateState();
	}

	return 0;
}