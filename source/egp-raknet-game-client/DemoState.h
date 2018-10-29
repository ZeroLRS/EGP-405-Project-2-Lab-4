#pragma once
class GraphicsSystem;
class UnitManager;
class GraphicsBufferManager;
class InputManager;
class EventSystem;
class BouncingBallManager;

class Sprite;
class GraphicsBuffer;

#include <chrono>

class DemoState
{
private:
	GraphicsSystem * mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	//UnitManager* mpUnitManager;
	BouncingBallManager* mpBouncingBallManager;
	InputManager* mpInputManager;

	Sprite* ballSprite;
	GraphicsBuffer* ballBuffer;

	bool initSDL();
	bool runLoop;
	bool recieveInput;

	//Timing
	std::chrono::time_point<std::chrono::system_clock> lastTime;
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> lastTimeMS;

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
	inline BouncingBallManager* getUnitManager() { return mpBouncingBallManager; };
	inline InputManager* getInputManager() { return mpInputManager; };
	inline bool canRecieveInput() { return recieveInput; };
	inline bool canRecieveInput(bool _flag) { return recieveInput = _flag; };
};

