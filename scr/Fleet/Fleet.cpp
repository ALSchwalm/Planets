
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

	unsigned int Fleet::move()
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

		unsigned int shipsLanded = 0;
		for (auto ship =ships.begin(); ship != ships.end(); )
		{
			auto ship_ptr = *ship;
			if (ship_ptr->move())
			{
				++shipsLanded;
				ship = ships.erase(std::find(ships.begin(), ships.end(), ship_ptr));
				delete ship_ptr;
			}
			else
			{
				++ship;
			}
		}

		return shipsLanded;
	}
}
