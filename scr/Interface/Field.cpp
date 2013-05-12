
#include "Interface/Field.h"
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
			box(fieldWin, 0, 0);
			for (auto planet : Game::planets)
			{
				if (planet->getOwner() == Game::player)
				{
					attron(COLOR_PAIR(1));
					mvwchgat(fieldWin, planet->getX(), planet->getY(), 1, A_BLINK, 1, NULL);
				}
				else if (planet->getOwner() != nullptr)
					mvwaddch(fieldWin, planet->getX(), planet->getY()-1, '_');

				mvwaddch(fieldWin, planet->getX(), planet->getY(), planet->getLetter());

				char populationBuffer[10];
				sprintf(populationBuffer, "%d", planet->getPopulation());
				waddstr(fieldWin, populationBuffer);
			}

			for (auto fleet : Game::fleets)
			{
				if (fleet->getOwner() == Game::player)
					mvwaddch(fieldWin, fleet->getX(), fleet->getY(), '*');
				else
					mvwaddch(fieldWin, fleet->getX(), fleet->getY(), '.');
			}

			wrefresh(fieldWin);
		}
	}
}
