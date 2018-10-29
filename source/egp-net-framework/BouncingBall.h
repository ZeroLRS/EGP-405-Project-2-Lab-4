#pragma once
#include "Vector2.h"
#include "egp-net/fw/egpNetSerializableData.h"
#include "RakNet/NetworkIDObject.h"

class BouncingBallManager;

class BouncingBall : public egpSerializableData
{
public:
	BouncingBall();

	const int radius = 30;

	Vector2 position;
	Vector2 velocity;

	void update(BouncingBallManager* manager, float dt);

	RakNet::NetworkIDObject netID;
	RakNet::NetworkID netID_int;

private:
	void unitCollision(BouncingBallManager* manager);
	void unitCollide(BouncingBall* ball);
	void boundaryCollide();
	void move(float dt);
	void addImpulse(Vector2 direction);

public:
	// override serialize from base class
	virtual int Serialize(RakNet::BitStream *bs) const;

	// override deserialize from base class
	virtual int Deserialize(RakNet::BitStream *bs);

	// aggregation
	// make your own cctor or assign op
	// cctor
	BouncingBall(const BouncingBall &) = delete;

	// assign
	BouncingBall &operator =(const BouncingBall &hrs) = delete;

	// mctor
	BouncingBall(BouncingBall &&) = delete;

	// move assign
	BouncingBall &operator =(BouncingBall &&) = delete;
};