
#include "Interface/CLI/Command.h"
#include "Interface/CLI/CLI.h"
#include "Planet/Planet.h"
#include <vector>
#include <sstream>
#include <cstdlib>

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

			Planet::Planet* source_planet = nullptr;
			Planet::Planet* destination_planet = nullptr;
			for (auto planet : Game::player->getPlanets())
			{
				if (planet->getLetter() == tokens[0].c_str()[0])
				{
					source_planet = planet;
					break;
				}
			}
			for (auto planet : Game::planets)
			{
				if (planet->getLetter() == tokens[1].c_str()[0])
				{
					destination_planet = planet;
					break;
				}
			}

			if (!source_planet or !destination_planet)
			{
				return false;
			}

			if (tokens.size() == 3)
			{
				if (atoi(tokens[2].c_str()) == 0)
					return false;
				else if (tokens[2][0] == '.')
					source_planet->launchFleetPercent(destination_planet, atoi(tokens[2].c_str()));
				else
					source_planet->launchFleetInt(destination_planet, atoi(tokens[2].c_str()));
			}
			else
				source_planet->launchFleetInt(destination_planet);

			return true;
		  }
	}
}
