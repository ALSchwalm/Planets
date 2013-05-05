
#include "Interface/Interface.h"
#include "Interface/CLI/CLI.h"

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

	    keypad(mainwin, true); 	//allow arrow/function keys
	    //nodelay(mainwin, true);	//do not wait for input
	    timeout(1);
	    noecho();	//do not echo user intput to screen

	    CLI::initialize();
	}
	void refreshView()
	{
//		if (helpView)
//			helpView->refreshView();
//		else
//			displayView->refreshView();
		wrefresh(CLI::lineWin);
	}

}
