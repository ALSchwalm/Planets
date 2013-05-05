
#include "Game/Game.h"
#include "Interface/Field.h"

#include <cstdlib>
#include <time.h>
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

	void setup(unsigned int numAI)
	{
		srand (time(NULL));

		Game::player = new Player::HumanPlayer(0);
		for (unsigned int ID=1; ID < numAI+1; ++ID)
		{
			aiPlayers.push_back(new Player::AIPlayer(ID));
		}

		for (unsigned int planet; planet < NUM_PLANETS; ++planet)
		{
			int temp_x, temp_y;
			getmaxyx(Interface::Field::fieldWin, temp_x, temp_y);

			/*
			 * For reasons I cannot explain. This fails if I perform the
			 * mod inside the new, or if I use LINES and COLS rather than
			 * the above function.
			 */

			temp_x = rand()%(temp_x-2)+1;
			temp_y = rand()%(temp_y-2)+1;

			planets.push_back(new Planet::Planet(temp_x, temp_y,  planet+65));
		}

	}
}
