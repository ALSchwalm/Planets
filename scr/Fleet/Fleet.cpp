
#include "Fleet/Fleet.h"
#include "Fleet/Ship.h"
#include "Utils/Pathing.h"
#include <limits.h>

using Utils::directions;

namespace Fleet
{

	Fleet::Fleet(Player::BasePlayer* _owner,
			Planet::Planet* _source,
			Planet::Planet* _destination,
			unsigned int population) :
			x(_source->getX()),
			y(_source->getY()),
			population(population),
			owner(_owner),
			source(_source),
			destination(_destination)
	{
		for(unsigned int i=0; i < population; ++i)
		{
			ships.push_back(new Ship(this, x, y));
		}
	}

	Fleet::~Fleet()
	{
		for(auto ship : ships)
		{
			delete ship;
		}
	}

	bool Fleet::move()
	{

		unsigned int shortest_distance = std::numeric_limits<unsigned int>::max();
		auto move_direction = directions[0];

		for (auto direction : directions)
		{
			if (Utils::getDistance(x+direction.first, y+direction.second, destination->getX(), destination->getY()) < shortest_distance)
			{
				shortest_distance = Utils::getDistance(x+direction.first, y+direction.second, destination->getX(), destination->getY());
				move_direction = direction;
			}
		}
		x+=move_direction.first;
		y+=move_direction.second;

		for (auto ship : ships)
		{
			ship->move();
		}

		if (destination->getX() == x and destination->getY() == y)
			return true;

		return false;
	}
}
