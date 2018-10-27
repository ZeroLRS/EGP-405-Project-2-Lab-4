#include "BouncingBall.h"

void BouncingBall::update()
{
	unitCollide();
	boundaryCollide();
	move();
}

void BouncingBall::unitCollide()
{

}

void BouncingBall::boundaryCollide()
{
	if (position.x >= 1280)
	{
		addImpulse(Vector2(-velocity.x * 2, 0));
	}
	if (position.x <= 0)
	{
		addImpulse(Vector2(velocity.x * 2, 0));
	}
	if (position.y >= 720)
	{
		addImpulse(Vector2(0, -velocity.y * 2));
	}
	if (position.y <= 0)
	{
		addImpulse(Vector2(0, velocity.y * 2));
	}
}

void BouncingBall::move()
{
	position += velocity;
}

void BouncingBall::addImpulse(Vector2 direction)
{
	velocity += direction;
}
