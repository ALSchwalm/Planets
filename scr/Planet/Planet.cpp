
#include "Planet/Planet.h"

namespace Planet
{
	Planet::Planet(unsigned int _x, unsigned int _y, const char _letter) :
			x(_x),
			y(_y),
			letter(_letter),
			population(0)
		{}

	void Planet::launchFleet(unsigned int size, Planet* destination)
	{

	}
}
