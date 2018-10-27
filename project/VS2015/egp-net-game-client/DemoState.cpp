#include "Header.h"
#include "BouncingBallManager.h"

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
	//mpUnitManager = new UnitManager();
	mpBouncingBallManager = new BouncingBallManager();
	mpInputManager = new InputManager();

	runLoop = true;

	ballBuffer = new GraphicsBuffer("circle.bmp", 32, 32);

	ballSprite = new Sprite(ballBuffer);

	mpBouncingBallManager->createBallUnit(Vector2(200, 200), 4);

	return true;
}

void DemoState::handleNetworking()
{
}

void DemoState::update()
{
	mpInputManager->updateKeyStates();

	//TODO: PASS IN DELTA TIME
	mpBouncingBallManager->update(1.0f);
}

void DemoState::render()
{
	//mpUnitManager->draw(mpGraphicsSystem);
	for (ballUnit* ball : mpBouncingBallManager->ourBallUnits)
	{
		getGraphicsSystem()->draw(ballSprite, ball->ball->position.x, ball->ball->position.y);
		printf("XY: %f, %f\n", ball->ball->position.x, ball->ball->position.y);
	}
	getGraphicsSystem()->flip();
}

void DemoState::exitLoop()
{
	runLoop = false;
}

bool DemoState::shouldLoop()
{
	return runLoop;
}