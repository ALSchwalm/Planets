
#include "Player/AIPlayer.h"
#include "Game/Game.h"
#include "Utils/Pathing.h"
#include <algorithm>

#include <cassert> //TODO remove this

namespace Player
{
	AIPlayer::AIPlayer(unsigned int _ID) :
		BasePlayer(_ID)
	{
	}

	Planet::Planet* AIPlayer::getSmallestPlanet(bool onlyOwned)
	{
		std::set<Planet::Planet*>::iterator smallest_iter;
		Planet::Planet* smallest = nullptr;
		//Find a planet which this player does not own to start the search

		if (onlyOwned)
		{
			smallest_iter = std::find_if(Game::planets.begin(), Game::planets.end(),
					[this](Planet::Planet* planet){return (planet->getOwner() != this and
							planet->getOwner() != nullptr);});
		}
		else
		{
			smallest_iter = std::find_if(Game::planets.begin(), Game::planets.end(),
					[this](Planet::Planet* planet){return planet->getOwner() != this;});
		}

		if (smallest_iter == Game::planets.end())
			return nullptr;
		else
			smallest = *smallest_iter;

		for(auto planet : Game::planets)
		{
			if(planet->getPopulation() <= smallest->getPopulation()
					and planet->getOwner() != this)
			{
				if (!onlyOwned)
					smallest = planet;
				else if (planet->getOwner() != nullptr)
					smallest = planet;
			}

		}
		return smallest;
	}

	Planet::Planet* AIPlayer::getSmallestOwnedPlanet()
	{
		return getSmallestPlanet(true);
	}

	unsigned int AIPlayer::getTotalPopulation()
	{
		unsigned int total=0;
		std::for_each(planets.begin(), planets.end(),
				[&](Planet::Planet* planet){total+=planet->getPopulation();});
		return total;
	}

	unsigned int AIPlayer::getLargestDistance(Planet::Planet* destination)
	{
		unsigned int largest = 0;
		for(auto planet : planets)
		{
			if (Utils::getDistance(planet->getX(), planet->getY(), destination->getX(), destination->getY()) > largest)
				largest = Utils::getDistance(planet->getX(), planet->getY(), destination->getX(), destination->getY());
		}
		return largest;
	}

	Planet::Planet* AIPlayer::getClosestPlanet(Planet::Planet* target)
	{
		auto closest = *planets.begin();

		for(auto planet : planets)
		{
			if (Utils::getDistance(planet->getX(), planet->getY(), target->getX(), target->getY()) <
					Utils::getDistance(closest->getX(), closest->getY(), target->getX(), target->getY()))
				closest = planet;
		}
		return closest;
	}

	void AIPlayer::move()
	{
		if (planets.size()==0 or getSmallestOwnedPlanet()==nullptr)
			return;

		Planet::Planet* target;

		if (getTotalPopulation() > getSmallestOwnedPlanet()->getPopulation()+
				getLargestDistance(getSmallestOwnedPlanet())*Planet::Planet::GROWTH_RATE + 1)
			target = getSmallestOwnedPlanet();
		else if (getTotalPopulation() > getSmallestPlanet()->getPopulation()+
				getLargestDistance(getSmallestPlanet())*Planet::Planet::GROWTH_RATE + 1)
			target = getSmallestPlanet();
		else
			return;

		auto current_fleet = std::find_if(fleets.begin(), fleets.end(),
				[&](Fleet::Fleet* fleet){return fleet->getDestination() == target;});

		if (current_fleet != fleets.end())
		{
			return;
		}

		float percent = static_cast<float>(target->getPopulation()+getLargestDistance(target)*
				Planet::Planet::GROWTH_RATE + 1)/getTotalPopulation();

		percent = (percent+1)/2;
		assert(percent*getTotalPopulation() >= target->getPopulation()*
				Planet::Planet::GROWTH_RATE + 1);


		for(auto planet : planets)
		{
			planet->launchFleetPercent(target, percent);
		}

	}
}
