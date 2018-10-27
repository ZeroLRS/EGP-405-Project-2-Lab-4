#pragma once

class DemoState;
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
	DemoState * localState;

	DataModel mCurrentDataModel;

public:
	ServerState();
	~ServerState();

	void updateDataPush();
	void updateDataShared();
	void updateDataCoupled();

	void render();

	inline DataModel getCurrentModel() { return mCurrentDataModel; };
	inline DataModel setCurrentModel(DataModel _nextModel) { return mCurrentDataModel = _nextModel; };
};

