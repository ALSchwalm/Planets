
#include "Fleet/Fleet.h"
#include "Utils/Pathing.h"
#include <limits.h>

namespace Fleet
{
	namespace
	{
		const std::vector<std::pair<int, int> > directions
		{
			std::pair<const int, const int>(0, 1),
			std::pair<const int, const int>(0, -1),
			std::pair<const int, const int>(1, 0),
			std::pair<const int, const int>(-1, 0)
		};
	}

	bool Fleet::move()
	{

		unsigned int shortest_distance = std::numeric_limits<unsigned int>::max();
		auto move_direction = directions[0];

		for (auto direction : directions)
		{
			if (Utils::getManhattanDistance(x+direction.first, y+direction.second, destination) < shortest_distance)
			{
				shortest_distance = Utils::getManhattanDistance(x+direction.first, y+direction.second, destination);
				move_direction = direction;
			}
		}
		x+=move_direction.first;
		y+=move_direction.second;

		if (destination->getX() == x and destination->getY() == y)
			return true;

		return false;
	}
}
