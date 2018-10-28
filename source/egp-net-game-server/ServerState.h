#pragma once

class DemoState;
class DemoServer;

namespace RakNet
{
	struct Packet;
}

enum DataModel
{
	OFFLINE,
	PUSH,
	SHARE,
	COUPLED
};

class ServerState
{
private:
	DemoState* localState;

	DataModel currentDataModel;
	const DemoServer* server;
	bool sendGameState;
	int updatesRecieved;

public:
	ServerState(DemoServer* _server);
	~ServerState();

	void updateDataPush();
	void updateDataShared();
	void updateDataCoupled();

	void handleInputPacket(RakNet::Packet _packet);
	void handleGameStatePacket(RakNet::Packet _packet);

	void render();

	inline DataModel getCurrentModel() { return currentDataModel; };
	inline DataModel setCurrentModel(DataModel _nextModel) { return currentDataModel = _nextModel; };
	inline bool shouldSendState() { return sendGameState; };
	inline bool shouldSendState(bool _flag) { return sendGameState = _flag; };
};

