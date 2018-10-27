#pragma once
class GraphicsSystem;
class UnitManager;
class GraphicsBufferManager;
class InputManager;
class EventSystem;

class DemoState
{
private:
	GraphicsSystem * mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	//UnitManager* mpUnitManager;
	InputManager* mpInputManager;

	bool initSDL();
	bool runLoop;
	bool recieveInput;

public:
	DemoState() = default;
	virtual ~DemoState() = default;

	static DemoState* getInstance();

	bool init();

	virtual void handleNetworking();
	virtual void update();
	virtual void render();

	void exitLoop();
	bool shouldLoop();

	inline GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };
	//inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline InputManager* getInputManager() { return mpInputManager; };
	inline bool canRecieveInput() { return recieveInput; };
	inline bool canRecieveInput(bool _flag) { return recieveInput = _flag; };
};

