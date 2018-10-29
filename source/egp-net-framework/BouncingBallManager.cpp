#include "BouncingBallManager.h"

void BouncingBallManager::update(float dt)
{
	std::lock_guard<std::mutex> lock(ballLock);
	for each (ballUnit* ball in ourBallUnits)
	{
		ball->ball->update(this, dt);
	}
}

ballUnit * BouncingBallManager::createBallUnit(Vector2 _position, Vector2 _velocity, int _id)
{
	std::lock_guard<std::mutex> lock(ballLock);
	ballUnit* newUnit = new ballUnit();
	newUnit->ball = new BouncingBall();
	newUnit->ball->position = _position;
	newUnit->ball->velocity = _velocity;
	newUnit->id = _id;

	ourBallUnits.push_back(newUnit);

	return newUnit;
}

int BouncingBallManager::Serialize(RakNet::BitStream * bs) const
{
	if (bs)
	{
		unsigned int totalSz = 0;

		totalSz += sizeof(ourBallUnits.size());
		bs->Write(ourBallUnits.size());

		for (ballUnit* b : ourBallUnits)
		{
			totalSz += sizeof(b->id);
			bs->Write(b->id);

			totalSz += b->ball->Serialize(bs);
		}

		return totalSz;
	}
	return 0;
}

int BouncingBallManager::Deserialize(RakNet::BitStream * bs)
{
	std::lock_guard<std::mutex> lock(ballLock);
	if (bs)
	{
		//clean up old ballunits
		ourBallUnits.clear();

		unsigned int totalSz = 0;
		size_t ballCount = 0;

		totalSz += sizeof(ballCount);
		bs->Read(ballCount);

		for (int i = 0; i < ballCount; i++)
		{
			ballUnit* newBall = new ballUnit();
			newBall->ball = new BouncingBall();
			totalSz += sizeof(newBall->id);
			bs->Read(newBall->id);

			totalSz += newBall->ball->Deserialize(bs);
			ourBallUnits.push_back(newBall);
		}

		return totalSz;
	}
	return 0;
}

BouncingBallManager* BouncingBallManager::getInstance()
{
	static BouncingBallManager instance;

	return &instance;
}
