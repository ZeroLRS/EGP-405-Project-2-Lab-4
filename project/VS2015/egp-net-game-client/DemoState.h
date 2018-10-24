#pragma once
class GraphicsSystem;
class UnitManager;
class GraphicsBufferManager;
class InputManager;
class EventSystem;

class DemoState
{
private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;
	InputManager* mpInputManager;

	bool initSDL();
	bool runLoop;

public:
	DemoState() = default;
	~DemoState() = default;

	static DemoState* getInstance();

	bool init();

	void handleNetworking();
	void update();
	void render();
	void exitLoop();
	bool shouldLoop();

	inline GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline InputManager* getInputManager() { return mpInputManager; };

};

