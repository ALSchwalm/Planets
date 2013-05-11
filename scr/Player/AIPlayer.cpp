
#include "Player/AIPlayer.h"
#include "Game/Game.h"
#include "Utils/Pathing.h"
#include <algorithm>

namespace Player
{
	AIPlayer::AIPlayer(unsigned int _ID) :
		BasePlayer(_ID)
	{
	}

	Planet::Planet* AIPlayer::getSmallestPlanet()
	{
		auto smallest = *std::find_if(Game::planets.begin(), Game::planets.end(),
				[this](Planet::Planet* planet){return planet->getOwner() != this;});

		for(auto planet : Game::planets)
		{
			if(planet->getPopulation() <= smallest->getPopulation()
					and planet->getOwner() != this)
				smallest = planet;
		}
		return smallest;
	}

	Planet::Planet* AIPlayer::getClosestPlanet(Planet::Planet* target)
	{
		auto closest = *planets.begin();
		for(auto planet : planets)
		{
			if (Utils::getManhattanDistance(planet->getX(), planet->getY(), target) <
					Utils::getManhattanDistance(closest->getX(), closest->getY(), target))
				closest = planet;
		}
		return closest;
	}

	void AIPlayer::move()
	{
		if (fleets.size() > 0)
			return;

		auto smallest = getSmallestPlanet();

		for(auto planet : planets)
		{
			planet->launchFleetInt(smallest);
		}

	}
}
