#include "../egp-net-game-server/DemoServer.h"
#include "../egp-net-game-server/ServerState.h"
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
		switch (state->getCurrentModel())
		{
			case(PUSH):
			{
				state->updateDataPush();
				break;
			}
			case(SHARE):
			{
				state->updateDataShared();
				break;
			}
			case(COUPLED):
			{
				state->updateDataCoupled();
				break;
			}
		}
	}

	return 0;
}