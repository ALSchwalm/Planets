
#ifndef PLANET_H_
#define PLANET_H_

#include "Player/BasePlayer.h"

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
		void setLetter(const char _letter) {letter = _letter;}

		void grow();

		bool launchFleetInt(Planet* destination, unsigned int size);
		bool launchFleetInt(Planet* destination);
		bool launchFleetPercent(Planet* destination, float size);
		bool launchFleetPercent(Planet* destination);

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
		 * How much population can leave a planet in one fleet
		 */
		static const unsigned int MAX_EGRESS = 10; //TODO read from config
		static constexpr float GROWTH_RATE = 0.03f;
	};
}

#endif
