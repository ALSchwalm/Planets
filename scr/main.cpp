
#include "Utils/curses.h"

int main()
{
	WINDOW * mainwin;

    if ( (mainwin = initscr()) == NULL ) {
		throw("Error initializing ncurses");
    }
	return 0;
}
