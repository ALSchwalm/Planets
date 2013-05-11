
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
			owner(_owner),
			partialPopulation(0.0f){}

	Planet::Planet(unsigned int _x, unsigned int _y, const char _letter, unsigned int initialPopulation) :
			x(_x),
			y(_y),
			letter(_letter),
			population(initialPopulation),
			owner(nullptr),
			partialPopulation(0.0f){}

	void Planet::setOwner(Player::BasePlayer* _owner)
	{
		 if (owner != nullptr)
		 {
			 owner->removePlanet(this);
		 }
		 _owner->addPlanet(this);
		 owner=_owner;
		 if (owner == Game::player)
				letter = toupper(letter);
		else
				letter = tolower(letter);
	}

	void Planet::grow()
	{
		partialPopulation += GROWTH_RATE;
		if (partialPopulation > 1)
			population += static_cast<int>(partialPopulation);
			partialPopulation -= static_cast<int>(partialPopulation);
	}

	void Planet::launchFleet()
	{
		if (fleetQueue.size() > 0)
		{
			Game::fleets.insert(fleetQueue.front());
			owner->addFleet(fleetQueue.front());
			fleetQueue.pop();
		}
	}

	bool Planet::launchFleetInt(Planet* destination, unsigned int size)
	{
		Fleet::Fleet* newFleet = nullptr;
		auto size_holder = size;

		if (owner == nullptr or size > population or size==0)
		{
			return false;
		}
		else if (size > MAX_EGRESS)
		{
			for (; size > MAX_EGRESS; size-=10)
			{
				newFleet = new Fleet::Fleet(owner, this, destination, MAX_EGRESS);
				fleetQueue.push(newFleet);
			}
			if (size > 0)
			{
				newFleet = new Fleet::Fleet(owner, this, destination, size);
				fleetQueue.push(newFleet);
			}
		}
		else
		{
			newFleet = new Fleet::Fleet(owner, this, destination, size);
			fleetQueue.push(newFleet);
		}
		population-=size_holder;


		return true;
	}

	bool Planet::launchFleetInt(Planet* destination)
	{
		return launchFleetInt(destination, population*owner->getMovePercent());
	}

	bool Planet::launchFleetPercent(Planet* destination)
	{
		return launchFleetInt(destination, population*owner->getMovePercent());
	}

	bool Planet::launchFleetPercent(Planet* destination, float size)
	{
		return launchFleetInt(destination, population*size);
	}
}
