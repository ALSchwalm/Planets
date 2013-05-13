#ifndef FLEET_H_
#define FLEET_H_

#include "Player/BasePlayer.h"
#include "Planet/Planet.h"

namespace Fleet
{
	class Ship;

	class Fleet
	{
	public:
		Fleet(Player::BasePlayer* _owner,
				Planet::Planet* _source,
				Planet::Planet* _destination,
				unsigned int population);

		~Fleet();

		unsigned int getX() const {return x;}
		unsigned int getY() const {return y;}
		unsigned int getSize() const {return population;}
		unsigned int getPopulation() const {return population;}

		Player::BasePlayer* getOwner() const {return owner;}
		Planet::Planet* getSource() const {return source;}
		Planet::Planet* getDestination() const {return destination;}

		std::vector<Ship*> & getShips(){return ships;}

		/*
		 * move() returns a bool representing whether the fleet
		 * reached its destination in this move.
		 */
		bool move();

	private:
		unsigned int x, y, population;

		Player::BasePlayer* owner;
		Planet::Planet* source;
		Planet::Planet* destination;

		std::vector<Ship*> ships;

	};
}

#endif
