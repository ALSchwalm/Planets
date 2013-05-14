#ifndef BASEPLAYER_H_
#define BASEPLAYER_H_

#include <vector>
#include <algorithm>

namespace Fleet
{
	class Fleet;
}

namespace Planet
{
	class Planet;
}

namespace Player
{
	class BasePlayer
	{
	public:
		BasePlayer(unsigned int _ID);

		unsigned int getMovePercent() const {return movePercent;}
		void setMovePercent(unsigned int _movePercent) {movePercent = _movePercent;}
		void incrementMovePercent();
		void decrementMovePercent();

		const unsigned int getID() const {return ID;}

		const std::vector<Planet::Planet*> & getPlanets() const {return planets;}
		void addPlanet(Planet::Planet* planet) {planets.push_back(planet);}
		void removePlanet(Planet::Planet* planet) { planets.erase(std::remove(planets.begin(), planets.end(), planet));}

		const std::vector<Fleet::Fleet*> & getFleets() const {return fleets;}
		void addFleet(Fleet::Fleet* fleet) {fleets.push_back(fleet);}
		void removeFleet(Fleet::Fleet* fleet) { fleets.erase(std::remove(fleets.begin(), fleets.end(), fleet));}

	protected:
		const unsigned int ID;
		unsigned int movePercent;
		std::vector<Planet::Planet*> planets;
		std::vector<Fleet::Fleet*> fleets;
	};
}

#endif
