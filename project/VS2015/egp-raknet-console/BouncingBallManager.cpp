#include "BouncingBallManager.h"

void BouncingBallManager::update(float dt)
{
	for each (ballUnit* ball in ourBallUnits)
	{
		ball->ball->update(this, dt);
	}
}

ballUnit * BouncingBallManager::createBallUnit(Vector2 _position, int _id)
{
	ballUnit* newUnit = new ballUnit;
	newUnit->ball = new BouncingBall();
	newUnit->ball->position = _position;
	newUnit->id = _id;

	ourBallUnits.push_back(newUnit);

	return newUnit;
}
