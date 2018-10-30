#include "Header.h"
#include "egp-net-framework/BouncingBallManager.h"
#include <mutex>

DemoState* DemoState::getInstance()
{
	static DemoState instance;

	return &instance;
}

bool DemoState::initSDL()
{
	return (SDL_Init(SDL_INIT_EVERYTHING) < 0) ? false : true;
}

bool DemoState::initPush()
{
	for (int i = 0; i < 3; i++)
	{
		int randomSeed = RakNet::RakPeerInterface::Get64BitUniqueRandomNumber();
		BouncingBall newBall;
		unsigned int packetSize = 0;
		newBall.position = Vector2(randomSeed % 1280, randomSeed % 720);
		newBall.velocity = Vector2(randomSeed % 200 + 200, randomSeed % 200 + 200);
		newBall.netID = RakNet::RakPeerInterface::Get64BitUniqueRandomNumber();

		RakNet::BitStream* bs = new RakNet::BitStream();
		packetSize += sizeof((char)DemoPeerManager::e_id_spawnNewBall);
		bs->Write((char)DemoPeerManager::e_id_spawnNewBall);

		packetSize += newBall.Serialize(bs);

		mpPeerManager->spawnNewBall(bs, packetSize);
	}
	return true;
}

bool DemoState::initShare()
{
	for (int i = 0; i < 3; i++)
	{
		int randomSeed = RakNet::RakPeerInterface::Get64BitUniqueRandomNumber();
		BouncingBall* newBall = new BouncingBall();
		newBall->position = Vector2(randomSeed % 1280, randomSeed % 720);
		newBall->velocity = Vector2(randomSeed % 200 + 200, randomSeed % 200 + 200);
		newBall->netID = RakNet::RakPeerInterface::Get64BitUniqueRandomNumber();
		mpBouncingBallManager->getInstance()->ourBallUnits.push_back(newBall);
	}
	return false;
}

bool DemoState::init()
{
	std::string modelSelect;
	std::cout << "Select Model:\n\tData (P)ush\n\tData (S)hare\n\tData (C)oupled\n";
	std::cin >> modelSelect;
	if (modelSelect[0] == 'p' || modelSelect[0] == 'P')
	{
		mSelectedModel = DATA_PUSH;
	}
	else if (modelSelect[0] == 's' || modelSelect[0] == 'S')
	{
		mSelectedModel = DATA_SHARE;
	}
	else if (modelSelect[0] == 'c' || modelSelect[0] == 'C')
	{
		mSelectedModel = DATA_COUPLED;
	}
	else
	{
		std::cout << "\n\nERROR, invalid input.\nStarting in non-networked mode.\n";
		system("pause");
		mSelectedModel = NOT_NETWORKED;
	}

	// Connect to server
	if (mSelectedModel != NOT_NETWORKED)
	{
		mpPeerManager = DemoPeerManager::getInstance();

		if (mpPeerManager->StartupNetworking(true, 0, 0, true) == 0)
		{
			std::cout << "Network startup failed.\n";
			system("pause");
			return false;
		}

		std::string ip;
		short port;
		std::cout << "Enter Server IP (or . for localhost):\n";
		std::cin >> ip;
		if (ip[0] == '.')
		{
			ip = "127.0.0.1";
		}
		std::cout << "Enter Server Port:\n";
		std::cin >> port;

		std::cout << "Connecting to server...\n";
		if (mpPeerManager->Connect(ip.c_str(), port) <= 0)
		{
			std::cout << "Could not connect.\n";
			system("pause");
			return false;
		}
	}

	if (!initSDL())
	{
		return false;
	}

	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->init();

	mpGraphicsBufferManager = new GraphicsBufferManager();
	//mpUnitManager = new UnitManager();
	mpBouncingBallManager = BouncingBallManager::getInstance();
	mpInputManager = new InputManager();

	runLoop = true;

	ballBuffer = new GraphicsBuffer("circle.bmp", 32, 32);

	ballSprite = new Sprite(ballBuffer);
	ballSprite->setHeight(32);
	ballSprite->setWidth(32);
	if (mSelectedModel == NOT_NETWORKED)
		mpBouncingBallManager->createBallUnit(Vector2(200, 200), Vector2(300, 300));

	//Timing
	lastTime = std::chrono::system_clock::now();
	lastTimeMS = std::chrono::time_point_cast<std::chrono::milliseconds>(lastTime);

	switch (mSelectedModel)
	{
	case DATA_PUSH:
		initPush();
		break;
	case DATA_SHARE:
		initShare();
		break;
	default:
		break;
	}

	return true;
}

void DemoState::handleNetworking()
{
}

void DemoState::update()
{
	if (mSelectedModel == NOT_NETWORKED || mSelectedModel == DATA_SHARE)
	{
		mpInputManager->updateKeyStates();

		std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
		std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> currentTimeMS
			= std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

		std::chrono::milliseconds elapsedChronoTime = currentTimeMS - lastTimeMS;

		float elapsedTime = (float)elapsedChronoTime.count();

		mpBouncingBallManager->update(elapsedTime);

		lastTimeMS = currentTimeMS;
	}

	if (mSelectedModel == DATA_SHARE)
	{
		unsigned int packetSize = 0;
		RakNet::BitStream* bs = new RakNet::BitStream();

		packetSize += sizeof((char)DemoPeerManager::e_id_requestUpdateBouncingBallsToServer);
		bs->Write((char)DemoPeerManager::e_id_requestUpdateBouncingBallsToServer);

		packetSize += mpBouncingBallManager->Serialize(bs);

		mpPeerManager->updateBouncingBalls(bs, packetSize);
	}
}

void DemoState::render()
{

	getGraphicsSystem()->clear();

	std::lock_guard<std::mutex> lock(mpBouncingBallManager->ballLock);

	for (BouncingBall* ball : mpBouncingBallManager->ourBallUnits)
	{
		getGraphicsSystem()->draw(ballSprite, ball->position.x, ball->position.y);
	}
	for (BouncingBall* ball : mpBouncingBallManager->otherBallUnits)
	{
		getGraphicsSystem()->draw(ballSprite, ball->position.x, ball->position.y);
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