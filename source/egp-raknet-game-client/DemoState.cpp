#include "Header.h"
#include "egp-net-framework/BouncingBallManager.h"

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
	ballSprite->setHeight(32);
	ballSprite->setWidth(32);
	mpBouncingBallManager->createBallUnit(Vector2(200, 200), Vector2(300, 300), 4);

	//Timing
	lastTime = std::chrono::system_clock::now();
	lastTimeMS = std::chrono::time_point_cast<std::chrono::milliseconds>(lastTime);

	return true;
}

void DemoState::handleNetworking()
{
}

void DemoState::update()
{
	mpInputManager->updateKeyStates();

	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> currentTimeMS
		= std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

	std::chrono::microseconds elapsedChronoTime = currentTimeMS - lastTimeMS;

	float elapsedTime = (float) elapsedChronoTime.count();

	mpBouncingBallManager->update(elapsedTime / 1000);

	lastTimeMS = currentTimeMS;
}

void DemoState::render()
{
	getGraphicsSystem()->clear();

	//mpUnitManager->draw(mpGraphicsSystem);
	for (ballUnit* ball : mpBouncingBallManager->ourBallUnits)
	{
		getGraphicsSystem()->draw(ballSprite, ball->ball->position.x, ball->ball->position.y);

		//printf("VXY: %f, %f\n", ball->ball->velocity.x, ball->ball->velocity.y);
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