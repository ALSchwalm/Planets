#ifndef FIELD_H_
#define FIELD_H_

#include "Interface/Interface.h"

#if _WIN32
# include "Utils/curses.h"
#elif __linux__
# include <ncurses.h>
#endif

namespace Interface
{
	namespace Field
	{
		void initialize();
		void update();

		extern WINDOW* fieldWin;
	}
}

#endif
