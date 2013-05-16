
#ifndef PLANET_H_
#define PLANET_H_

#include "Player/BasePlayer.h"
#include <queue>

namespace Fleet
{
	class Fleet;
}


namespace Planet
{
	class Planet
	{
	public:

		Planet(unsigned int _x,
				unsigned int _y,
				const char _letter,
				unsigned int initialPopulation=0);

		Planet(Player::BasePlayer*,
				unsigned int _x,
				unsigned int _y,
				const char _letter,
				unsigned int initialPopulation=0);

		unsigned int getX() const {return x;}
		unsigned int getY() const {return y;}

		char getLetter() const {return letter;}
		unsigned int getPopulation() const {return population;}
		Player::BasePlayer* getOwner() const {return owner;}

		void setOwner(Player::BasePlayer* _owner);
		void setPopulation(unsigned int _population) {population = _population;}

		void grow();

		/*
		 * Launch the oldest fleet in the fleetQueue
		 */
		void launchFleet();

		/*
		 * These command create the fleet and store them in the fleetQueue
		 */
		bool launchFleetInt(Planet* destination, unsigned int size);
		bool launchFleetInt(Planet* destination);
		bool launchFleetPercent(Planet* destination, float size);
		bool launchFleetPercent(Planet* destination);

		static const float GROWTH_RATE;

	private:
		const unsigned int x;
		const unsigned int y;
		char letter;
		unsigned int population;
		Player::BasePlayer* owner;

		/*
		 * In all other cases, population should be an int. However, there
		 * must be a variable to hold the >1 population growth that occurs per
		 * tick.
		 */
		float partialPopulation;

		/*
		 * Stores the fleets created when a user launches population > MAX_EGRESS
		 */
		std::queue<Fleet::Fleet*> fleetQueue;
		/*
		 * How much population can leave a planet in one fleet
		 */
		static const unsigned int MAX_EGRESS;

	};
}

#endif
