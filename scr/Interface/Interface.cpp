
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

	    CLI::initialize();
	    Field::initialize();

	    keypad(mainwin, true);
	    wtimeout(CLI::lineWin, 1);
	    noecho();	//do not echo user intput to screen
	}
	void refresh()
	{
		Field::update();
		wrefresh(Field::fieldWin);
		wrefresh(CLI::lineWin);
	}

}
