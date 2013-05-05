#ifndef FLEET_H_
#define FLEET_H_

#include "Player/BasePlayer.h"
#include "Planet/Planet.h"

namespace Fleet
{
	class Fleet
	{
	public:
		Fleet(Player::BasePlayer* _owner,
				Planet::Planet* _source,
				Planet::Planet* _destination,
				unsigned int population) :
				x(source->getX()),
				y(source->getY()),
				population(population),
				owner(_owner),
				source(_source),
				destination(_destination)
		{}

		unsigned int getX() const {return x;}
		unsigned int getY() const {return y;}
		unsigned int getSize() const {return population;}

		Player::BasePlayer* getOwner() const {return owner;}
		Planet::Planet* getSource() const {return source;}
		Planet::Planet* getDestination() const {return destination;}

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

	};
}

#endif
