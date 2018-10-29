#pragma once
#include <vector>
#include "BouncingBall.h"
#include <mutex>

struct ballUnit
{
	BouncingBall* ball;
	int id;
};

class BouncingBallManager : public egpSerializableData
{
	
public:
	BouncingBallManager() {};

	std::vector<ballUnit*> ourBallUnits;
	std::vector<ballUnit*> otherBallUnits;
	void update(float dt);

	ballUnit* createBallUnit(Vector2 _position, Vector2 _velocity, int _id);
	
	// override serialize from base class
	virtual int Serialize(RakNet::BitStream *bs) const;

	// override deserialize from base class
	virtual int Deserialize(RakNet::BitStream *bs);

	std::mutex ballLock;

	// aggregation
	// make your own cctor or assign op
	// cctor
	BouncingBallManager(const BouncingBallManager &) = delete;

	// assign
	BouncingBallManager &operator =(const BouncingBallManager &hrs) = delete;

	// mctor
	BouncingBallManager(BouncingBallManager &&) = delete;

	// move assign
	BouncingBallManager &operator =(BouncingBallManager &&) = delete;

	static BouncingBallManager* getInstance();
private:

};