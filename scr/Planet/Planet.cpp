
#include "Planet/Planet.h"

namespace Planet
{
	Planet::Planet(unsigned int _x, unsigned int _y, const char _letter) :
			x(_x),
			y(_y),
			letter(_letter),
			population(0)
		{}

	void Planet::launchFleetInt(unsigned int size, Planet* destination)
	{

	}

	void Planet::launchFleetPercent(float size, Planet* destination)
	{
		launchFleetInt(population*size, destination);
	}
}
