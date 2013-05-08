
#include "Game/Game.h"
#include "Interface/Field.h"
#include "Interface/CLI/CLI.h"

#include <cstdlib>
#include <time.h>
#include <stdexcept>
#if _WIN32
# include "Utils/curses.h"
#elif __linux__
# include <ncurses.h>
#endif

namespace Game
{
	Player::HumanPlayer* player = nullptr;
	std::vector<Player::AIPlayer*> aiPlayers;
	std::vector<Fleet::Fleet*> fleets;
	std::vector<Planet::Planet*> planets;

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


	void setup(unsigned int numAI)
	{
		srand (time(NULL));

		if (NUM_PLANETS < numAI + 1)
		{
			throw(std::runtime_error("Insufficient planets for number of players."));
		}

		Game::player = new Player::HumanPlayer(0);
		for (unsigned int ID=1; ID < numAI+1; ++ID)
		{
			aiPlayers.push_back(new Player::AIPlayer(ID));
		}

		for (unsigned int planet; planet < NUM_PLANETS; ++planet)
		{
			unsigned int temp_x, temp_y;
			getmaxyx(Interface::Field::fieldWin, temp_x, temp_y);

			/*
			 * For reasons I cannot explain. This fails if I perform the
			 * mod inside the new, or if I use LINES and COLS rather than
			 * the above function.
			 */
			do
			{
				temp_x = rand()%(temp_x-2)+1;
				temp_y = rand()%(temp_y-2)+1;
			} while (!validPosition(temp_x, temp_y));

			unsigned int initial_pop = (rand()%(MAX_INITIAL_POP - MIN_INITIAL_POP))+MIN_INITIAL_POP;

			planets.push_back(new Planet::Planet(temp_x, temp_y,  planet+65, initial_pop));
		}
		planets[0]->setOwner(player);
		planets[0]->setPopulation(PLAYER_STARTING_POP);


	}

	void update()
	{
		Interface::Field::update();
#if _WIN32
		waddstr(Interface::CLI::lineWin, " \b");
		wrefresh(Interface::CLI::lineWin);
#endif

		for (auto fleet : fleets)
		{
			fleet->move();
		}

	}


}
