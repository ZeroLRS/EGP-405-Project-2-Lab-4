///* File created by:
//* Lucas Spiker and Cory Smith
//* For:
//* Lab 3 on 10/1/2018
//* EGP-405 by Dan Buckstein
//*
//* “We certify that this work is entirely our own.
//*	The assessor of this project may reproduce
//*	this project and provide copies to other academic staff,
//*	and/or communicate a copy of this project to a plagiarism-checking service,
//*	which may retain a copy of the project on its database.”
//*/
//
//#pragma once
//
//#include "RakNet/RakPeerInterface.h"
//#include "RakNet/MessageIdentifiers.h"
//#include "RakNet/RakNetTypes.h"
//#include "RakNet/BitStream.h"
//
//#include <string>
//#include <vector>
//#include <mutex>
//
//enum GameMessages
//{
//	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM
//};
//
//struct userID
//{
//	std::string username;
//	RakNet::RakNetGUID guid;
//};
//
//class Networking
//{
//
//private:
//	RakNet::RakPeerInterface *peer;
//	RakNet::Packet *packet;
//
//public:
//	Networking();
//	~Networking();
//	void HandlePackets();
//	void init();
//
//	bool isServer;
//	std::string username;
//	
//	static Networking* getInstance()
//	{
//		static Networking instance;
//
//		return &instance;
//	}
//};
