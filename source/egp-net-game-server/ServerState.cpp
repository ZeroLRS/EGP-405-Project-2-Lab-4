#include "ServerState.h"
#include <iostream>
#include <string>
#include "DemoServer.h"
#include "../project/VS2015/egp-net-game-client/DemoState.h"
ServerState::ServerState(DemoServer* _server)
{
	server = _server;

	//localState = new DemoState();
	//localState->init();

	//localState->canRecieveInput(false);
}


ServerState::~ServerState()
{
	//if (localState)
	//{
	//	delete localState;
	//}
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
	default:
		return "";
	}
}

void ServerState::simulateDemo()
{
	//TODO: PASS IN DELTA TIME
	mpBouncingBallManager->update(1.0f);
}

void ServerState::updateDataPush()
{
	//update regularly
	//if input events are recieved from client recreate them locally
	//localState->update();


	if(shouldSendState())
		server->broadcastDemoState();
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

	if (shouldSendState())
	{
		//send state to all clients
		server->broadcastDemoState();

		//prevent state from being sent again until all packets are recieved
		updatesRecieved = 0;
		shouldSendState(false);
	}
}

void ServerState::handleInputPacket(const RakNet::Packet *const _packet)
{

}

void ServerState::handleGameStatePacket(const RakNet::Packet *const _packet)
{
	if (currentDataModel == COUPLED)
	{
		
	}
}

void ServerState::render()
{
	std::cout << "Current data model: " << getModelAsString(getCurrentModel()) << '\n';
}

void ServerState::exitLoop()
{
	runLoop = false;
}

bool ServerState::shouldLoop()
{
	return runLoop;
}
