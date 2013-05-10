
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
					mvwchgat(fieldWin, planet->getX(), planet->getY(), 1, A_STANDOUT  , 0, NULL);
				mvwaddch(fieldWin, planet->getX(), planet->getY(), planet->getLetter());
				char populationBuffer[10];
				sprintf(populationBuffer, "%d", planet->getPopulation());
				waddstr(fieldWin, populationBuffer);

			}

			for (auto fleet : Game::fleets)
			{
				mvwaddch(fieldWin, fleet->getX(), fleet->getY(), '.');
			}

			wrefresh(fieldWin);
		}
	}
}
