
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
		static std::vector<std::string> tokenize(std::string command)
		{
			std::string buf;
			std::stringstream ss(command);

			std::vector<std::string> tokens;

			while (ss >> buf)
				tokens.push_back(buf);

			return tokens;
		}

		static const std::vector<Planet::Planet*> getSources(std::string sourceList)
		{
			if (sourceList == "all")
			{
				return Game::player->getPlanets();
			}

			std::vector<Planet::Planet*> sources;
			for (auto letter : sourceList)
			{
				for(auto planet : Game::player->getPlanets())
				{
					if (tolower(letter) == tolower(planet->getLetter()))
					{
						sources.push_back(planet);
					}
				}
			}
			return sources;
		}

		bool runCommand(std::string command)
		{
		  std::vector<std::string> tokens = tokenize(command);

		/*
		 * Valid commands are of the form:
		 * 	source(s) destination number_of_ships
		 * 	source(s) destination percent_of_ships
		 * 	or
		 * 	source destination  <--- Where the percent_of_ships will be the default
		 */
		if (tokens.size() != 2 && tokens.size() != 3)
			return false;

		std::vector<Planet::Planet*> sources = getSources(tokens[0]);

		Planet::Planet* destination_planet = nullptr;
		for (auto planet : Game::planets)
		{
			if (planet->getLetter() == tokens[1].c_str()[0] or
					toupper(planet->getLetter()) == tokens[1].c_str()[0])
			{
				destination_planet = planet;
				break;
			}
		}

		if (sources.size() < 1 or !destination_planet)
		{
			return false;
		}

		if (tokens.size() == 3)
		{
			for (auto source_planet : sources)
			{
				/*
				 * atoi returns false if the conversion is invalid
				 */
				if (!atoi(tokens[2].c_str()))
					return false;
				else if (tokens[2][0] == '.')
					source_planet->launchFleetPercent(destination_planet, atoi(tokens[2].c_str()));
				else
					source_planet->launchFleetInt(destination_planet, atoi(tokens[2].c_str()));
			}
		}
		else
		{
			for (auto source_planet : sources)
				source_planet->launchFleetInt(destination_planet);
		}

		return true;
		}
	}
}
