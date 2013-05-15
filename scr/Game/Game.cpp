
#include "Game/Game.h"
#include "Interface/Field.h"
#include "Interface/CLI/CLI.h"
#include "Utils/Config.h"
#include "Utils/Pathing.h"

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
	const unsigned int NUM_PLANETS = 			Utils::Config::getInstance().getValue("Game", "NUM_PLANETS");
	const unsigned int NUM_AI_PLAYERS= 			Utils::Config::getInstance().getValue("Game", "NUM_AI_PLAYERS");
	const unsigned int PLANET_DENSITY = 		Utils::Config::getInstance().getValue("Game", "PLANET_DENSITY");
	const unsigned int MAX_INITIAL_POP = 		Utils::Config::getInstance().getValue("Game", "MAX_INITIAL_POP");
	const unsigned int MIN_INITIAL_POP = 		Utils::Config::getInstance().getValue("Game", "MIN_INITIAL_POP");
	const unsigned int PLAYER_STARTING_POP = 	Utils::Config::getInstance().getValue("Game", "PLAYER_STARTING_POP");
	const unsigned int AI_STARTING_POP = 		Utils::Config::getInstance().getValue("Game", "AI_STARTING_POP");


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
			if ( Utils::getDistance(x, y, planet->getX(), planet->getY()) <= PLANET_DENSITY)
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

		if (NUM_PLANETS > 26)
		{
			throw(std::runtime_error("Too many planets. Valid NUM_PLANET range is 1-26."));
		}

		/*
		 * Player IDs are 1 indexed as they correspond to the COLOR_PAIR used to color
		 * thier planets/ships. ncurses uses a 1 indexed system for these pairs, and so
		 * the IDs are 1 indexed.
		 */
		Game::player = new Player::HumanPlayer(1);
		for (unsigned int ID=2; ID < NUM_AI_PLAYERS+2; ++ID)
		{
			aiPlayers.push_back(new Player::AIPlayer(ID));
		}

		unsigned int max_x, max_y, temp_x, temp_y;
		getmaxyx(Interface::Field::fieldWin, max_x, max_y);

		for (unsigned int planet; planet < NUM_PLANETS; ++planet)
		{
			do
			{
				temp_x = rand()%(max_x-2)+1;
				temp_y = rand()%(max_y-6)+3;
			} while (!validPosition(temp_x, temp_y));

			unsigned int initial_pop = (rand()%(MAX_INITIAL_POP - MIN_INITIAL_POP))+MIN_INITIAL_POP;

			planets.insert(new Planet::Planet(temp_x, temp_y,  planet+97, initial_pop));
		}

		auto playerPlanet = std::find_if(planets.begin(), planets.end(),
				[](Planet::Planet* planet){return planet->getLetter() == 'a';});
		(*playerPlanet)->setOwner(player);
		(*playerPlanet)->setPopulation(PLAYER_STARTING_POP);

		for(auto aiPlayer : aiPlayers)
		{
			/*
			 * Player IDs are 1 indexed, and the first AI player should own 'b'. The first AI player ID is
			 * 2, so 2+96=98 = ASCII 'b'
			 */
			auto planet = std::find_if(planets.begin(), planets.end(),
					[&](Planet::Planet* planet){return static_cast<unsigned int>(planet->getLetter()) == aiPlayer->getID()+96;});
			(*planet)->setOwner(aiPlayer);
			(*planet)->setPopulation(AI_STARTING_POP);
		}

	}

	void update()
	{

		Interface::Field::update();
		Interface::CLI::update();
#if _WIN32
		//In windows terminals, trick to focus the CLI again
		waddstr(Interface::CLI::lineWin, " \b");
		wrefresh(Interface::CLI::lineWin);
#endif

		for (auto fleet = fleets.begin(); fleet != fleets.end(); )
		{
			auto fleet_ptr = *(fleet);

			/*
			 * Fleet::move() returns and unsigned int equal to the number
			 * of ships which landed with this move;
			 */

			if(auto landed = fleet_ptr->move())
			{
				Planet::Planet* tempDestination = fleet_ptr->getDestination();
				if (tempDestination->getOwner() != fleet_ptr->getOwner())	//If the destination is enemy/neutral
				{
					if (landed > tempDestination->getPopulation()) //If the planet has been taken
					{

						tempDestination->setPopulation(landed - tempDestination->getPopulation());
						tempDestination->setOwner(fleet_ptr->getOwner()); //This also sets the letter/capitalization
					}
					else	//The planet has not been taken
					{
						tempDestination->setPopulation(tempDestination->getPopulation() - landed);
					}
				}
				else
				{
					tempDestination->setPopulation(tempDestination->getPopulation() + landed);
				}
			}

			if (fleet_ptr->getShips().size() == 0)
			{
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

		/*
		 * Begin check for GAME OVER conditions
		 */

		//find first non-neutral planet with different owner than the first
		auto firstOtherPlanet = std::find_if(planets.begin(), planets.end(),
				[&](Planet::Planet* planet){return (planet->getOwner() != (*planets.begin())->getOwner()) and
						(planet->getOwner() != nullptr);});

		//if there is no non-neutral planet with owner different from the first, game over.
		if (firstOtherPlanet == planets.end())
		{
			//Do not end the game if there are any ships from other players in flight
			if (std::find_if(fleets.begin(), fleets.end(),
					[&](Fleet::Fleet* fleet){return fleet->getOwner() != (*planets.begin())->getOwner();}) ==
							fleets.end())
			{
				Interface::showEnd(*planets.begin());
				end();
			}
		}
	}

	void end()
	{
		endwin();
		exit(EXIT_SUCCESS);
	}


}
