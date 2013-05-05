#ifndef PATHING_H_
#define PATHING_H_

#include <math.h>

namespace Planet
{
	class Planet;
}

namespace Utils
{
	inline unsigned int getManhattanDistance(unsigned int x, unsigned int y, Planet::Planet* destination)
	{
		return abs(x - destination->getX()) + abs(y - destination->getY());
	}
}

#endif
