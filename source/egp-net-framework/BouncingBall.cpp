#include "BouncingBall.h"
#include "BouncingBallManager.h"

BouncingBall::BouncingBall()
{

}

void BouncingBall::update(BouncingBallManager* manager, float dt)
{
	printf("Pos XY: %f, %f\n", position.x, position.y);
	unitCollision(manager);
	boundaryCollide();
	move(dt);
}

void BouncingBall::unitCollision(BouncingBallManager* manager)
{
	for each (ballUnit* ball in manager->ourBallUnits)
	{
		// Make sure we don't count self-collision
		if (!(ball->ball->position == position))
			unitCollide(ball->ball);
	}
	for each (ballUnit* ball in manager->otherBallUnits)
	{
		unitCollide(ball->ball);
	}
}

void BouncingBall::unitCollide(BouncingBall * ball)
{
	float distx, disty, totaldist;

	// Circle collision (x2-x1)^2 + (y1-y2)^2 <= r^2
	distx = (ball->position.x - position.x);

	disty = (ball->position.y - position.y);

	totaldist = distx * distx + disty * disty;

	if (totaldist <= radius * radius)
	{
		// Add force equal to the inverse of the distance wrt radius
		// ie. the closer they are at collision, the farther they bounce
		addImpulse(Vector2(radius - distx, radius - disty));
	}
}

void BouncingBall::boundaryCollide()
{
	if (position.x > 1280)
	{
		addImpulse(Vector2(-velocity.x * 2, 0));
		position.x = 1280;
	}
	if (position.x < 0)
	{
		addImpulse(Vector2(-velocity.x * 2, 0));
		position.x = 0;
	}
	if (position.y > 720)
	{
		addImpulse(Vector2(0, -velocity.y * 2));
		position.y = 720;
	}
	if (position.y < 0)
	{
		addImpulse(Vector2(0, -velocity.y * 2));
		position.y = 0;
	}
}

void BouncingBall::move(float dt)
{
	// Move by our velocity per second
	position += velocity * (dt / 1000);

	// Push velocity towards normalization
	//velocity
}

void BouncingBall::addImpulse(Vector2 direction)
{
	velocity += direction;
	//printf("Impulse XY: %f, %f\n", direction.x, direction.y);
}

int BouncingBall::Serialize(RakNet::BitStream * bs) const
{
	if (bs)
	{
		unsigned int totalSz = 0;

		totalSz += sizeof(position);
		bs->Write(position);

		totalSz += sizeof(velocity);
		bs->Write(velocity);

		return totalSz;
	}
	return 0;
}

int BouncingBall::Deserialize(RakNet::BitStream * bs)
{
	if (bs)
	{
		unsigned int totalSz = 0;

		totalSz += sizeof(position);
		bs->Read(position);

		totalSz += sizeof(velocity);
		bs->Read(velocity);

		return totalSz;
	}
	return 0;
}
