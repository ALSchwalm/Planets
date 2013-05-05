
#include "Interface/Field.h"
#include "Game/Game.h"

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
			for (auto planet : Game::planets)
			{
				mvwaddch(fieldWin, planet->getX(), planet->getY(), planet->getLetter());
			}
			wrefresh(fieldWin);
		}
	}
}
