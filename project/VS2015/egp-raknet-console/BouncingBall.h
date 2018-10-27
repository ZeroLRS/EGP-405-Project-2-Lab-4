#pragma once
#include "Vector2.h"

class BouncingBall
{
public:
	Vector2 position;
	Vector2 velocity;

	void update();

private:
	void unitCollide();
	void boundaryCollide();
	void move();
	void addImpulse(Vector2 direction);

};