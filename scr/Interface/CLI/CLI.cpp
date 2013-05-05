
#include "Interface/CLI/CLI.h"
#include <string>

namespace Interface
{
	namespace CLI
	{
		WINDOW * CLIwin;
		WINDOW * lineWin;
		std::string line;

		void initialize()
		{

			CLIwin = subwin(mainwin, 3, COLS, 0, 0);
			box(CLIwin, 0, 0);
			refresh();
			mvaddstr(1, 2, "Command:");

			lineWin = subwin(CLIwin, 1, COLS-12, 1, 11);

		}

		void handleInput()
		{

			int c = wgetch(lineWin);
			switch(c)
			{
			case 27:	//esc
				break;
			case 10:	//enter
				line="";
				break;
			case 9:		//tab
				break;

			case KEY_BACKSPACE:
			case 127:	//linux backspace
			case 8:		//windows windows backspace
				waddch(lineWin, '\b');
				wdelch(lineWin);
				if (line != "")
					line.erase(line.end()-1);
				break;
			case ERR:
				break;
			default:
				waddch(lineWin, c);
				line += c;
				break;
			}
		}

	}
}



