#pragma once
#include <vector>
#include "BouncingBall.h"

struct ballUnit
{
	BouncingBall* ball;
	int id;
};

class BouncingBallManager
{
	
public:
	std::vector<ballUnit*> ourBallUnits;
	std::vector<ballUnit*> otherBallUnits;
	void update(float dt);

	ballUnit* createBallUnit(Vector2 _position, Vector2 _velocity, int _id);

private:

};