/*
	egpNetServerPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Server manager source.

	Additional contributions by (and date): 

*/

#include "DemoPeerManager.h"
#include <iostream>
#include "BouncingBallManager.h"
#include <mutex>

int DemoPeerManager::ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const
{
	// ****TO-DO: implement server-specific packet processor
	
	switch (packet->data[0])
	{
		case(e_id_gameStateUpdate):
		{
			RakNet::BitStream stream(packet->data, packet->length, false);

			stream.IgnoreBytes(sizeof((char)e_id_gameStateUpdate));

			BouncingBallManager::getInstance()->Deserialize(&stream);
			break;
		}
		case(e_id_spawnNewBall):
		{
			RakNet::BitStream stream(packet->data, packet->length, false);

			stream.IgnoreBytes(sizeof((char)e_id_spawnNewBall));

			BouncingBall newBall;
			newBall.Deserialize(&stream);

			printf("New Ball Pos: %f, %f\nNew Ball Vel: %f, %f",
				newBall.position.x, newBall.position.y,
				newBall.velocity.x, newBall.velocity.y);

			BouncingBallManager::getInstance()->createBallUnit(newBall.position, newBall.velocity, 3);
			break;
		}
		default:
			std::cout << "ID" << packet->data[0] << std::endl;
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
	static DemoPeerManager instance;

	return &instance;
}

void DemoPeerManager::sendGameStatePacket(RakNet::BitStream* _gsStream, unsigned int _gsSize)
{
	SendPacket(_gsStream, -1, true, true);
}

void DemoPeerManager::spawnNewBall(RakNet::BitStream * _bStream, unsigned int _bSize)
{
	SendPacket(_bStream, -1, true, true);
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