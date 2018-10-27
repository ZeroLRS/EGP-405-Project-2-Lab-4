#include "fw/DemoServer.h"
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
}

int main(int const argc, char const *const *const argv)
{
	DemoServer* server = new DemoServer();

	if (!initServer(server))
	{
		return -1;
	}

	while (1)
	{
		switch (server->getCurrentModel())
		{
			case(PUSH):
			{
				server->updateDataPush();
				break;
			}
			case(SHARE):
			{
				server->updateDataShared();
				break;
			}
			case(COUPLED):
			{
				server->updateDataCoupled();
				break;
			}
		}
	}

	return 0;
}