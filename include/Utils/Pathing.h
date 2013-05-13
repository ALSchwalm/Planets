#ifndef PATHING_H_
#define PATHING_H_

#include <math.h>

namespace Planet
{
	class Planet;
}

namespace Utils
{

	const std::vector<std::pair<int, int> > directions
	{
		std::pair<const int, const int>(0, 1),
		std::pair<const int, const int>(0, -1),

		std::pair<const int, const int>(1, 1),
		std::pair<const int, const int>(1, -1),
		std::pair<const int, const int>(1, 0),

		std::pair<const int, const int>(-1, 1),
		std::pair<const int, const int>(-1, 0),
		std::pair<const int, const int>(-1, -1)
	};


	inline unsigned int getManhattanDistance(unsigned int x, unsigned int y, Planet::Planet* destination)
	{
		return abs(x - destination->getX()) + abs(y - destination->getY());
	}

	//Accepts signed ints because the difference (i.e. x2 - x1) could be negative
	inline unsigned int getDistance(int x1, int y1, int x2, int y2)
	{
		return sqrt( pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0));
	}
}

#endif
