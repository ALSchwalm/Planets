
#include "Interface/Interface.h"
#include "Interface/CLI/CLI.h"
#include "Interface/Field.h"

#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace Interface
{
	WINDOW * mainwin;

	void initialize()
	{
	    if ( (mainwin = initscr()) == NULL ) {
			throw(std::runtime_error("Error initializing ncurses"));
	    }

	    if (has_colors())
	    {
	    	start_color();
	    	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	    	init_pair(2, COLOR_RED, COLOR_BLACK);
	    	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	    	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	    }
	    CLI::initialize();
	    Field::initialize();

	    keypad(mainwin, true);
	    wtimeout(CLI::lineWin, 0);
	    noecho();	//do not echo user intput to screen
	}

	void showPause()
	{
		waddstr(CLI::lineWin, "Press any key to begin.");
		wrefresh(CLI::lineWin);
		getch();
		wclear(CLI::lineWin);
	}

	void showEnd(Planet::Planet*)
	{
		Field::update();	//update the field so the last planet will show the new owner
		unsigned int max_x, max_y;
		getmaxyx(Field::fieldWin, max_y, max_x);

		mvwaddstr(Field::fieldWin, max_y/2, max_x/2-5, "GAME OVER.");
		wrefresh(Field::fieldWin);
		while (getch() != 10)
		{
			//To not exit until the user presses enter
		}

	}

	void refresh()
	{
		wrefresh(CLI::lineWin);
	}

}
