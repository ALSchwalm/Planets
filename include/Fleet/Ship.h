#ifndef SHIP_H_
#define SHIP_H_

#include "Player/BasePlayer.h"
#include "Planet/Planet.h"
#include "Fleet/Fleet.h"

namespace Fleet
{
	class Ship
	{
	public:
		Ship(Fleet* _parentFleet);
		Ship(Fleet* _parentFleet, unsigned int _x, unsigned int _y);

		unsigned int getX(){return x;}
		unsigned int getY(){return y;}
		Planet::Planet* getSource() const {return parentFleet->getSource();}
		Planet::Planet* getDestination() const {return parentFleet->getDestination();}
		Player::BasePlayer* getOwner() const {return parentFleet->getOwner();}

		bool move();

	private:
		std::vector<Ship*>getOtherShips();

		Fleet* parentFleet;
		unsigned int x, y;

		static constexpr float CLUMP_FACTOR = 1.2f;

	};
}

#endif
