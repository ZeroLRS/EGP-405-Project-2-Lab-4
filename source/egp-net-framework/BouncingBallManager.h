#pragma once
#include <vector>
#include "BouncingBall.h"
#include <mutex>
#include "RakNet/NetworkIDManager.h"

class BouncingBallManager : public egpSerializableData
{
	
public:
	BouncingBallManager()
	{}

	std::vector<BouncingBall*> ourBallUnits;
	std::vector<BouncingBall*> otherBallUnits;
	void update(float dt);

	BouncingBall* createBallUnit(Vector2 _position, Vector2 _velocity);
	
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