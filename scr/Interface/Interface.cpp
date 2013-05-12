
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
	    	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	    }
	    CLI::initialize();
	    Field::initialize();

	    keypad(mainwin, true);
	    wtimeout(CLI::lineWin, 0);
	    noecho();	//do not echo user intput to screen
	}

	void pause()
	{
		waddstr(CLI::lineWin, "Press any key to begin.");
		wrefresh(CLI::lineWin);
		getch();
		wclear(CLI::lineWin);
	}

	void refresh()
	{
		wrefresh(CLI::lineWin);
	}

}
