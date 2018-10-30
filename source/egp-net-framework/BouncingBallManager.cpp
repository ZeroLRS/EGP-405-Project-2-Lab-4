#include "BouncingBallManager.h"
#include "RakNet/RakPeerInterface.h"

void BouncingBallManager::update(float dt)
{
	std::lock_guard<std::mutex> lock(ballLock);
	for each (BouncingBall* ball in ourBallUnits)
	{
		ball->update(this, dt);
	}
}

BouncingBall * BouncingBallManager::createBallUnit(Vector2 _position, Vector2 _velocity)
{
	std::lock_guard<std::mutex> lock(ballLock);
	BouncingBall* newUnit = new BouncingBall();
	newUnit = new BouncingBall();
	newUnit->position = _position;
	newUnit->velocity = _velocity;
	newUnit->netID = RakNet::RakPeerInterface::Get64BitUniqueRandomNumber();

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

		for (BouncingBall* b : ourBallUnits)
		{

			totalSz += b->Serialize(bs);
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
		//ourBallUnits.clear();

		unsigned int totalSz = 0;
		size_t ballCount = 0;

		totalSz += sizeof(ballCount);
		bs->Read(ballCount);

		for (int i = 0; i < ballCount; i++)
		{
			BouncingBall* newBall = new BouncingBall();
			newBall = new BouncingBall();

			totalSz += newBall->Deserialize(bs);

			bool found = false;
			for (BouncingBall* currentBall : ourBallUnits)
			{
				if (currentBall->netID == newBall->netID)
					found = true;
			}

			if (!found)
			{
				ourBallUnits.push_back(newBall);
			}
		}

		return totalSz;
	}
	return 0;
}

int BouncingBallManager::DeserializeOtherUnits(RakNet::BitStream * bs)
{
	std::lock_guard<std::mutex> lock(ballLock);
	if (bs)
	{

		unsigned int totalSz = 0;
		size_t ballCount = 0;

		totalSz += sizeof(ballCount);
		bs->Read(ballCount);

		for (int i = 0; i < ballCount; i++)
		{
			BouncingBall* newBall = new BouncingBall();
			newBall = new BouncingBall();

			totalSz += newBall->Deserialize(bs);

			bool found = false;
			for (BouncingBall* currentBall : otherBallUnits)
			{
				if (currentBall->netID == newBall->netID)
					found = true;
			}

			if (!found)
			{
				otherBallUnits.push_back(newBall);
			}
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
