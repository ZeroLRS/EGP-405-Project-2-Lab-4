/*
	egpNetServerPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Server manager source.

	Additional contributions by (and date): 

*/

#include "DemoPeerManager.h"

int DemoPeerManager::ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const
{
	// ****TO-DO: implement server-specific packet processor
	
	switch (packet->data[0])
	{
		case(e_id_gameStateUpdate):
		{
			break;
		}
		default:
			break;
	}

	//if list of units is recieved send them to the unit manager in serverstate
	//--//
	//if inputs are recieved and current model is data push send input events to event system
	return 0;
}


DemoPeerManager::DemoPeerManager()
{
}

DemoPeerManager::~DemoPeerManager()
{
	// ****TO-DO
}

DemoPeerManager* DemoPeerManager::getInstance()
{
	static DemoPeerManager* instance;

	return instance;
}

//void DemoPeerManager::sendAllPackets()
//{
//	for (auto packet : packetsThisFrame)
//	{
//		SendPacket()
//	}
//}


//void DemoServer::broadcastDemoState() const
//{
//	broadcastDemoState(-1);
//}
//
//void DemoServer::broadcastDemoState(int _indexToOmit) const
//{
//	RakNet::BitStream stream;
//
//	stream.Write(e_id_gameStateUpdate);
//
//	//TO-DO: serialize all units
//
//	SendPacket(&stream, _indexToOmit, true, true);
//}