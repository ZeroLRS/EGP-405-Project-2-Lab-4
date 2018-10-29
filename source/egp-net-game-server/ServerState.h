#pragma once
#include <map>
#include <vector>

//class DemoState;
class DemoPeerManager;
class BallUnit;
class BouncingBallManager;
class InputManager;

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
	//DemoState* localState;

	BouncingBallManager* mpBouncingBallManager;
	InputManager* mpInputManager;

	DataModel currentDataModel;
	bool runLoop;
	bool sendGameState;
	int updatesRecieved;

	void simulateDemo();
	void updateDataPush();
	void updateDataShared();
	void updateDataCoupled();
	void switchDataModel(DataModel _nextModel);
	void broadcastDemoState();
	void broadcastDemoState(int _indexToOmit);

public:
	ServerState();
	~ServerState();

	void updateState();

	void handleGameStatePacket(const RakNet::Packet *const _packet);

	void render();

	inline DataModel getCurrentModel() { return currentDataModel; };
	inline DataModel setCurrentModel(DataModel _nextModel) { return currentDataModel = _nextModel; };
	inline BouncingBallManager* getUnitManager() { return mpBouncingBallManager; };
	inline bool shouldSendState() { return sendGameState; };
	inline bool shouldSendState(bool _flag) { return sendGameState = _flag; };
	void exitLoop();
	bool shouldLoop();
};

