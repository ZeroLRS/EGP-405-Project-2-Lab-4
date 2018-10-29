#include "BouncingBall.h"
#include "BouncingBallManager.h"

BouncingBall::BouncingBall()
{

}

void BouncingBall::update(BouncingBallManager* manager, float dt)
{
	unitCollision(manager);
	boundaryCollide();
	move(dt);
}

void BouncingBall::unitCollision(BouncingBallManager* manager)
{
	for each (BouncingBall* ball in manager->ourBallUnits)
	{
		// Make sure we don't count self-collision
		if (!(ball->position == position))
			unitCollide(ball);
	}
	for each (BouncingBall* ball in manager->otherBallUnits)
	{
		unitCollide(ball);
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
		//position.x += radius - distx;
		//position.y += radius - disty;
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

	// Push velocity towards 200, 200
	float time = dt / 1000;
	float destX = velocity.x >= 0 ? 200.0f : -200.0f;
	float destY = velocity.y >= 0 ? 200.0f : -200.0f;
	velocity.x = abs(velocity.x * (1 - time)) > abs(destX) ? velocity.x * (1 - time) : destX;
	velocity.y = abs(velocity.y * (1 - time)) > abs(destY) ? velocity.y * (1 - time) : destY;

	//printf("t vx vy %f %f %f\n", time, velocity.x, velocity.y);
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

		totalSz += sizeof(RakNet::NetworkID);
		bs->Write(netID_int);

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

		netID.SetNetworkIDManager(BouncingBallManager::getInstance()->netIDManager);

		totalSz += sizeof(RakNet::NetworkID);
		bs->Read(netID_int);

		BouncingBall* existingBall = netID.GetNetworkIDManager()->GET_OBJECT_FROM_ID<BouncingBall*>(netID_int);
		if (existingBall == nullptr)
		{
			netID.SetNetworkID(netID_int);
		}
		else
		{
			for (BouncingBall* currentBall : BouncingBallManager::getInstance()->ourBallUnits)
			{
				if (currentBall->netID_int == netID_int)
				{
					currentBall->position = position;
					currentBall->velocity = velocity;
					return totalSz;
				}
			}
		}

		return totalSz;
	}
	return 0;
}
