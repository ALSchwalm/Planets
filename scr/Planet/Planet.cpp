
#include "Planet/Planet.h"
#include "Game/Game.h"
#include "Fleet/Fleet.h"
#include <stdexcept>

namespace Planet
{
	Planet::Planet(Player::BasePlayer* _owner, unsigned int _x, unsigned int _y, const char _letter, unsigned int initialPopulation) :
			x(_x),
			y(_y),
			letter(_letter),
			population(initialPopulation),
			owner(_owner){}

	Planet::Planet(unsigned int _x, unsigned int _y, const char _letter, unsigned int initialPopulation) :
			x(_x),
			y(_y),
			letter(_letter),
			population(initialPopulation),
			owner(nullptr){}

	void Planet::launchFleetInt(unsigned int size, Planet* destination)
	{
		if (owner == nullptr)
		{
			throw(std::runtime_error("Attempt to launch fleet from unowned planet"));
		}
		Fleet::Fleet* newFleet = new Fleet::Fleet(owner, this, destination, size);
		Game::fleets.push_back(newFleet);
		owner->addFleet(newFleet);
	}

	void Planet::launchFleetPercent(float size, Planet* destination)
	{
		launchFleetInt(population*size, destination);
	}
}
