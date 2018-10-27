/*
	egpNetServerPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Server manager source.

	Additional contributions by (and date): 

*/

#include "DemoServer.h"


int DemoServer::ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const
{
	// ****TO-DO: implement server-specific packet processor
	
	return 0;
}


DemoServer::DemoServer()
{
	// ****TO-DO
}

DemoServer::~DemoServer()
{
	// ****TO-DO
}

void DemoServer::updateDataPush()
{
	
}

void DemoServer::updateDataShared()
{
}

void DemoServer::updateDataCoupled()
{
}
