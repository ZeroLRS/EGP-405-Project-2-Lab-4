#include "ServerState.h"
#include <iostream>
#include <string>
#include "egp-net-framework/BouncingBallManager.h"
#include "egp-net-framework/DemoPeerManager.h"

ServerState::ServerState()
{
	//server = _server;

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

void ServerState::updateState()
{

	switch (getCurrentModel())
	{
		case(PUSH):
		{
			updateDataPush();
			break;
		}
		case(SHARE):
		{
			updateDataShared();
			break;
		}
		case(COUPLED):
		{
			updateDataCoupled();
			break;
		}
		default:
		{
			return;
		}
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
	simulateDemo();

	if (shouldSendState())
		return;//server->broadcastDemoState();
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
		//server->broadcastDemoState();

		//prevent state from being sent again until all packets are recieved
		updatesRecieved = 0;
		shouldSendState(false);
	}
}

void ServerState::switchDataModel(DataModel _nextModel)
{
	switch (_nextModel)
	{
		//case(PUSH):
		//{
		//	updateDataPush();
		//	break;
		//}
		//case(SHARE):
		//{
		//	updateDataShared();
		//	break;
		//}
		case(COUPLED):
		{
			updatesRecieved = 0;
			shouldSendState(false);
			break;
		}
		default:
		{
			break;
		}
	}

	currentDataModel = _nextModel;
}

void ServerState::handleGameStatePacket(const RakNet::Packet *const _packet)
{
	//if coupled combine
	if (currentDataModel == COUPLED)
	{
		//mpBouncingBallManager->


		++updatesRecieved;
	}
	else if(currentDataModel == SHARE)
	{
		
	}
}

void ServerState::render()
{
	system("cls");

	std::cout << "Current data model: " << getModelAsString(getCurrentModel()) << '\n'
		<< "1 - PUSH || 2 - SHARED || 3 - COUPLED\n";
}

void ServerState::exitLoop()
{
	runLoop = false;
}

bool ServerState::shouldLoop()
{
	return runLoop;
}

void ServerState::broadcastDemoState()
{
	broadcastDemoState(-1);
}

void ServerState::broadcastDemoState(int _indexToOmit)
{
	RakNet::BitStream stream;

	stream.Write(DemoPeerManager::e_id_gameStateUpdate);

	//TO-DO: serialize all units

	//DemoPeerManager::getInstance()->SendPacket(&stream, _indexToOmit, true, true);
}