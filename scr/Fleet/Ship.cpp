
#include "Fleet/Ship.h"
#include "Utils/Pathing.h"
#include <limits.h>

using Utils::directions;

namespace Fleet
{
	float Ship::CLUMP_FACTOR = Utils::Config::getInstance().getValue("Ship", "CLUMP_FACTOR") * 0.01f;

	Ship::Ship(Fleet* _parentFleet) :
			parentFleet(_parentFleet),
			x(0),
			y(0)
	{}

	Ship::Ship(Fleet* _parentFleet, unsigned int _x, unsigned int _y) :
			parentFleet(_parentFleet),
			x(_x),
			y(_y)
	{}

	std::vector<Ship*>Ship::getOtherShips()
	{
		auto ships = parentFleet->getShips();
		return std::vector<Ship*>( ships.begin(), std::remove_if(ships.begin(), ships.end(),
				[this](Ship* ship){return ship == this;}));
	}

	bool Ship::move()
	{

		std::vector<float> moveValue(directions.size());

		for(unsigned int directionIndex=0; directionIndex < directions.size(); ++directionIndex)
		{
			for(auto ship : getOtherShips())
			{
				if (ship->getX() == x+directions[directionIndex].first and
						ship->getY() == y+directions[directionIndex].second)
				{
					moveValue[directionIndex]+=CLUMP_FACTOR;
				}
			}

//			moveValue[directionIndex] += Utils::getDistance(x+directions[directionIndex].first,
//					y+directions[directionIndex].second, parentFleet->getDestination()->getX(),
//					parentFleet->getDestination()->getY());

			moveValue[directionIndex] += Utils::getDistance(x+directions[directionIndex].first,
					y+directions[directionIndex].second, parentFleet->getX(),
					parentFleet->getY());
		}

		unsigned int moveDirection = 0;

		for(unsigned int i=0; i < moveValue.size(); ++i)
		{
			if (moveValue[i] < moveValue[moveDirection])
				moveDirection=i;
		}

		x += directions[moveDirection].first;
		y += directions[moveDirection].second;

		if (x == parentFleet->getDestination()->getX() and
				y == parentFleet->getDestination()->getY())
			return true;

		return false;


	}
}
