/*
	egpNetServerPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Server manager source.

	Additional contributions by (and date): 

*/

#include "DemoServer.h"
#include "ServerState.h"

int DemoServer::ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const
{
	// ****TO-DO: implement server-specific packet processor
	
	//if list of units is recieved send them to the unit manager in serverstate
	//--//
	//if inputs are recieved and current model is data push send input events to event system
	return 0;
}


DemoServer::DemoServer()
{
	currentState = new ServerState(this);
}

DemoServer::~DemoServer()
{
	// ****TO-DO
}

bool DemoServer::hasClient(RakNet::RakNetGUID _clientID)
{
	for (auto ID : connectedClients)
	{
		if (ID == _clientID)
			return true;
	}

	return false;
}

void DemoServer::addClient(RakNet::RakNetGUID _ID)
{
	if (hasClient(_ID))
		return;

	connectedClients.push_back(_ID);
}

void DemoServer::removeClient(RakNet::RakNetGUID _ID)
{
	for (auto iter = connectedClients.begin(); iter != connectedClients.end(); ++iter)
	{
		if ((*iter) == _ID)
		{
			connectedClients.erase(iter);

			return;
		}
	}

}

void DemoServer::broadcastDemoState()
{
	broadcastDemoState(-1);
}

void DemoServer::broadcastDemoState(int _indexToOmit)
{
	RakNet::BitStream stream;

	stream.Write(e_id_gameStateUpdate);

	//TO-DO: serialize all units

	SendPacket(&stream, _indexToOmit, true, true);
}
