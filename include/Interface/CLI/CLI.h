#ifndef CLI_H_
#define CLI_H_

#if _WIN32
# include "Utils/curses.h"
#elif __linux__
# include <ncurses.h>
#endif

#include "Interface/Interface.h"
#include <vector>

namespace Interface
{
	namespace CLI
	{

		void initialize();
		void refresh();
		extern WINDOW * CLIwin;
		extern WINDOW *	lineWin;
		void handleInput();
	}
}

#endif
