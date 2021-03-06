#ifndef INTERFACE_H_
#define INTERFACE_H_

#if _WIN32
# include "Utils/curses.h"
#elif __linux__
# include <ncurses.h>
#endif

#include <memory>

namespace Planet
{
	class Planet;
}


namespace Interface
{

	void initialize();
	void refresh();
	void showPause();
	void showEnd(Planet::Planet*);

	extern WINDOW* mainwin;
}
#endif
