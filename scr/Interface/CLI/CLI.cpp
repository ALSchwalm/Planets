
#include "Interface/CLI/CLI.h"
#include "Interface/CLI/Command.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include <string>
#include <cstdlib>

namespace Interface
{
	namespace CLI
	{
		WINDOW* CLIwin;
		WINDOW* lineWin;
		WINDOW* percentWin;
		std::string line;

		void initialize()
		{

			CLIwin = subwin(mainwin, 3, COLS-6, 0, 0);
			box(CLIwin, 0, 0);
			mvaddstr(1, 2, "Command:");
			wrefresh(CLIwin);
			lineWin = subwin(CLIwin, 1, COLS-18, 1, 11);

			percentWin = subwin(mainwin, 3, 6, 0, COLS-6);
			box(percentWin, 0, 0);
		}

		void handleInput()
		{
			int c = wgetch(lineWin);

			switch(c)
			{
			case 27:	//esc
				Game::end();
				break;
			case 10:	//enter
				runCommand(line);
				wclear(lineWin);
				line="";
				break;
			case KEY_UP:
				Game::player->incrementMovePercent();
				break;
			case KEY_DOWN:
				Game::player->decrementMovePercent();
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

		void update()
		{
			//wclear(percentWin);
			box(percentWin, 0, 0);
			auto percent = Utils::convert<std::string>(Game::player->getMovePercent());
			percent+="%";
			mvwaddstr(percentWin, 1, 1, percent.c_str());
			wrefresh(percentWin);
		}

	}
}



