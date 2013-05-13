
#include "Game/Game.h"
#include "Interface/Field.h"
#include "Interface/CLI/CLI.h"

#include <cstdlib>
#include <time.h>
#include <stdexcept>
#include <algorithm>

#if _WIN32
# include "Utils/curses.h"
#elif __linux__
# include <ncurses.h>
#endif

namespace Game
{
	Player::HumanPlayer* player = nullptr;
	std::vector<Player::AIPlayer*> aiPlayers;
	std::set<Fleet::Fleet*> fleets;
	std::set<Planet::Planet*> planets;

	/*
	 * Guarantee planets are not very close together
	 */
	static bool validPosition(unsigned int x, unsigned int y)
	{
		for (auto planet : planets)
		{
			if ((planet->getX() < x+PLANET_DENSITY and planet->getX() > x-PLANET_DENSITY ) and
				(planet->getY() < y+PLANET_DENSITY and planet->getY() > y-PLANET_DENSITY ))
				return false;
		}
		return true;
	}


	void setup()
	{
		srand (time(NULL));

		if (NUM_PLANETS < NUM_AI_PLAYERS + 1)
		{
			throw(std::runtime_error("Insufficient planets for number of players."));
		}

		Game::player = new Player::HumanPlayer(0);
		for (unsigned int ID=1; ID < NUM_AI_PLAYERS+1; ++ID)
		{
			aiPlayers.push_back(new Player::AIPlayer(ID));
		}

		for (unsigned int planet; planet < NUM_PLANETS; ++planet)
		{
			unsigned int max_x, max_y, temp_x, temp_y;
			getmaxyx(Interface::Field::fieldWin, max_x, max_y);

			/*
			 * For reasons I cannot explain. This fails if I perform the
			 * mod inside the new, or if I use LINES and COLS rather than
			 * the above function.
			 */
			do
			{
				temp_x = rand()%(max_x-2)+1;
				temp_y = rand()%(max_y-6)+3;
			} while (!validPosition(temp_x, temp_y));

			unsigned int initial_pop = (rand()%(MAX_INITIAL_POP - MIN_INITIAL_POP))+MIN_INITIAL_POP;

			planets.insert(new Planet::Planet(temp_x, temp_y,  planet+97, initial_pop));
		}
		(*planets.begin())->setOwner(player);
		(*planets.begin())->setPopulation(PLAYER_STARTING_POP);

		auto planet = planets.begin();
		for(auto aiPlayer : aiPlayers)
		{
			std::advance(planet, 1);
			(*planet)->setOwner(aiPlayer);
			(*planet)->setPopulation(AI_STARTING_POP);
		}

	}

	void update()
	{

		Interface::Field::update();
#if _WIN32
		//In windows terminals, trick to focus the CLI again
		waddstr(Interface::CLI::lineWin, " \b");
		wrefresh(Interface::CLI::lineWin);
#endif

		for (auto fleet = fleets.begin(); fleet != fleets.end(); )
		{
			auto fleet_ptr = *(fleet);

			/*
			 * Fleet::move() returns true when a fleet has reached its destination
			 */

			if(fleet_ptr->move())
			{
				Planet::Planet* tempDestination = fleet_ptr->getDestination();
				if (tempDestination->getOwner() != fleet_ptr->getOwner())	//If the destination is enemy/neutral
				{
					if (fleet_ptr->getPopulation() > tempDestination->getPopulation()) //If the planet has been taken
					{

						tempDestination->setPopulation(fleet_ptr->getPopulation() - tempDestination->getPopulation());
						tempDestination->setOwner(fleet_ptr->getOwner()); //This also sets the letter/capitalization
					}
					else	//The planet has not been taken
					{
						tempDestination->setPopulation(tempDestination->getPopulation() - fleet_ptr->getPopulation());
					}
				}
				else
				{
					tempDestination->setPopulation(tempDestination->getPopulation() + fleet_ptr->getPopulation());
				}

				fleet_ptr->getOwner()->removeFleet(fleet_ptr);
				fleet = fleets.erase(std::find(fleets.begin(), fleets.end(), fleet_ptr));
				delete fleet_ptr;
			}
			else
			{
				++fleet;
			}
		}

		for (auto planet : planets)
		{
			if (planet->getOwner() != nullptr)
				planet->grow();
			planet->launchFleet();
		}

		for (auto aiPlayer : aiPlayers)
		{
			aiPlayer->move();
		}

		//find first non-neutral planet with different owner than the first
		auto firstOtherPlanet = std::find_if(planets.begin(), planets.end(),
				[&](Planet::Planet* planet){return (planet->getOwner() != (*planets.begin())->getOwner()) and
						(planet->getOwner() != nullptr);});

		//if there is no non-neutral planet with owner different from the first, game over.
		if (firstOtherPlanet == planets.end() and fleets.size() == 0)
		{
			Interface::showEnd(*planets.begin());
			end();
		}
	}

	void end()
	{
		endwin();
		exit(EXIT_SUCCESS);
	}


}
