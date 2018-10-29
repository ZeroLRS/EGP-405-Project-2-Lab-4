#include "egp-net-framework/DemoPeerManager.h"
#include "ServerState.h"
#include <iostream>

bool initServer(DemoPeerManager* _server)
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