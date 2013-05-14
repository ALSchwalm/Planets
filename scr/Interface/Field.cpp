
#include "Interface/Field.h"
#include "Fleet/Ship.h"
#include "Game/Game.h"
#include <cstdlib>

namespace Interface
{
	namespace Field
	{
		WINDOW* fieldWin;

		void initialize()
		{
			fieldWin = subwin(mainwin, LINES-3, COLS, 3, 0);
			box(fieldWin, 0, 0);
			wrefresh(fieldWin);
		}

		void update()
		{
			wclear(fieldWin);

			for (auto fleet : Game::fleets)
			{
				for (auto ship : fleet->getShips())
				{
					attron(COLOR_PAIR(ship->getOwner()->getID()));
					if (ship->getOwner() == Game::player)
						mvwaddch(fieldWin, ship->getX(), ship->getY(), '*' | COLOR_PAIR(ship->getOwner()->getID()));
					else
						mvwaddch(fieldWin, ship->getX(), ship->getY(), '.' | COLOR_PAIR(ship->getOwner()->getID()));
				}
			}

			for (auto planet : Game::planets)
			{
				if (planet->getOwner() == Game::player)
				{
					attron(COLOR_PAIR(planet->getOwner()->getID()));
					mvwaddch(fieldWin, planet->getX(), planet->getY(), planet->getLetter() | COLOR_PAIR(1));
				}
				else if (planet->getOwner() != nullptr)
				{
					attron(COLOR_PAIR(2));
					mvwaddch(fieldWin, planet->getX(), planet->getY()-1, '_' | COLOR_PAIR(planet->getOwner()->getID()));
					mvwaddch(fieldWin, planet->getX(), planet->getY(), planet->getLetter() | COLOR_PAIR(planet->getOwner()->getID()));
				}
				else
				{
					mvwaddch(fieldWin, planet->getX(), planet->getY(), planet->getLetter());
				}

				char populationBuffer[10];
				sprintf(populationBuffer, "%d", planet->getPopulation());
				waddstr(fieldWin, populationBuffer);
			}

			box(fieldWin, 0, 0);
			wrefresh(fieldWin);
		}
	}
}
