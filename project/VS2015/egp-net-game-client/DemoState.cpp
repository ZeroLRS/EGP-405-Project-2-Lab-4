#include "Header.h"

DemoState* DemoState::getInstance()
{
	static DemoState instance;

	return &instance;
}

bool DemoState::initSDL()
{
	return (SDL_Init(SDL_INIT_EVERYTHING) < 0) ? false : true;
}

bool DemoState::init()
{
	if (!initSDL())
	{
		return false;
	}

	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->init();

	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
	mpInputManager = new InputManager();

	runLoop = true;

	return true;
}

void DemoState::handleNetworking()
{
}

void DemoState::update()
{
	//TODO: CHANGE TO DELTA TIME
	mpInputManager->updateKeyStates();
	mpUnitManager->update(1.0f);
}

void DemoState::render()
{
	mpUnitManager->draw(mpGraphicsSystem);
}

void DemoState::exitLoop()
{
	runLoop = false;
}

bool DemoState::shouldLoop()
{
	return runLoop;
}