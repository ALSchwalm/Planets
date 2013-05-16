
#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "Player/BasePlayer.h"

namespace Player
{
	class AIPlayer : public BasePlayer
	{
	public:
		AIPlayer(unsigned int _ID);

		void move();

	private:
		Planet::Planet* getSmallestPlanet(bool onlyOwned=false);
		Planet::Planet* getSmallestOwnedPlanet();
		Planet::Planet* getClosestPlanet(Planet::Planet*);
		unsigned int getLargestDistance(Planet::Planet*);
		unsigned int getTotalPopulation();
	};
}

#endif
