#include "ServerState.h"
#include "../egp-net-game-client/DemoState.h"
#include <iostream>
#include <string>

ServerState::ServerState()
{
	localState = new DemoState();
	localState->init();

	localState->canRecieveInput(false);
}


ServerState::~ServerState()
{
	if (localState)
	{
		delete localState;
	}
}

std::string getModelAsString(DataModel _model)
{
	switch (_model)
	{
	case(OFFLINE):
		return "Offline";
	case(PUSH):
		return "Push";
	case(SHARE):
		return "Shared";
	case(COUPLED):
		return "Coupled";
	}
}

void ServerState::updateDataPush()
{
	//update regularly
	//if input events are recieved from client recreate them locally
}

void ServerState::updateDataShared()
{
	//recieve networking events
	//immidiately broadcast them to all clients
}

void ServerState::updateDataCoupled()
{
	//wait to recieve all messages from clients (has counter of num connected)
	//when all are recieved set positions and broadcast to all clients
	//if there are conflicting positions average them
}

void ServerState::render()
{
	std::cout << "Current data model: " << getModelAsString(getCurrentModel()) << '\n';
}