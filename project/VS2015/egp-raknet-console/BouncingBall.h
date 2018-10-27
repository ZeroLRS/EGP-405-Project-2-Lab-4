#pragma once
#include "Vector2.h"

class BouncingBallManager;

class BouncingBall
{
public:
	BouncingBall();

	const int radius = 10;

	Vector2 position;
	Vector2 velocity;

	void update(BouncingBallManager* manager, float dt);

private:
	void unitCollision(BouncingBallManager* manager);
	void unitCollide(BouncingBall* ball);
	void boundaryCollide();
	void move(float dt);
	void addImpulse(Vector2 direction);
};