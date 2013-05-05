
#include "Interface/CLI/Command.h"
#include <vector>
#include <sstream>

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

			return true;
		  }
	}
}
