#ifndef BASEPLAYER_H_
#define BASEPLAYER_H_

#include "Planet/Planet.h"
#include <vector>
#include <algorithm>

namespace Player
{
	class BasePlayer
	{
	public:
		BasePlayer(unsigned int _ID);

		float getMovePercent() const {return movePercent;}
		void setMovePercent(float _movePercent) {movePercent = _movePercent;}

		const unsigned int getID() const {return ID;}

		const std::vector<Planet::Planet*> & getPlanets() const {return planets;}
		void addPlanet(Planet::Planet* planet) {planets.push_back(planet);}
		void removePlanet(Planet::Planet* planet) { planets.erase(std::remove(planets.begin(), planets.end(), planet));}

	private:
		const unsigned int ID;
		float movePercent;
		std::vector<Planet::Planet*> planets;
	};
}

#endif
