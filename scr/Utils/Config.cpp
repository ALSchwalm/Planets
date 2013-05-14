
#include "Utils/Config.h"

namespace Utils
{
	Config& Config::getInstance()
	{
		static Config c;
		return c;
	}


	Config::Config() :
		ini(std::string("config.ini"))
	{
		if (!ini.Parse())
		{
			create_ini();
		}
	};


	const unsigned int Config::getValue(std::string section, std::string value)
	{
		ini.Select(section);
		auto ini_value = ini.Get(value, -1);
		if (ini_value == -1)
		{
			throw(std::runtime_error(std::string("Unable to locate value for ") + section + std::string(".") + value));
			return 0;
		}
		else
		{
			return ini_value;
		}
	}

	void Config::create_ini()
	{
		ini.Create("Game");
		ini.Select("Game");
		ini.Set("NUM_PLANETS", 15);
		ini.Set("NUM_AI_PLAYERS", 2);
		ini.Set("PLANET_DENSITY", 6);
		ini.Set("MAX_INITIAL_POP", 75);
		ini.Set("MIN_INITIAL_POP", 5);
		ini.Set("PLAYER_STARTING_POP", 100);
		ini.Set("AI_STARTING_POP", 100);

		ini.Create("Planet");
		ini.Select("Planet");
		ini.Set("MAX_EGRESS", 100);
		ini.Set("GROWTH_RATE", 3);

		ini.Create("Ship");
		ini.Select("Ship");
		ini.Set("CLUMP_FACTOR", 80);


		ini.Save("config.ini");

	}
}
