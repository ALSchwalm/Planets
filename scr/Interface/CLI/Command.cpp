
#include "Interface/CLI/Command.h"
#include "Interface/CLI/CLI.h"
#include <vector>
#include <sstream>

#include "Game/Game.h" //TODO remove this

namespace Interface
{
	namespace CLI
	{
		  bool runCommand(std::string command)
		  {
			std::string buf;
			std::stringstream ss(command);

			std::vector<std::string> tokens;

			while (ss >> buf)
				tokens.push_back(buf);

			/*
			 * Valid commands are of the form:
			 * 	source destination number_of_ships
			 * 	source destination percent_of_ships
			 * 	or
			 * 	source destination  <--- Where the percent_of_ships will be the default
			 */
			if (tokens.size() != 2 && tokens.size() != 3)
				return false;

			Game::planets[0]->launchFleetInt(0, Game::planets[1]);

			return true;
		  }
	}
}
