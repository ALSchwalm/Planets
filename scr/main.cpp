
#include "Game/Game.h"
#include "Time/TimeManager.h"
#include "Interface/Interface.h"
#include "Interface/CLI/CLI.h"
#include <iostream>

int main()
{

	try
	{
		Interface::initialize();
		Game::setup();
		Game::update();
		Interface::showPause();

		while(true)
		{
			Time::TimeManager::getInstance().tick();
			Time::TimeManager::getInstance().capFPS();
			Interface::refresh();
			Interface::CLI::handleInput();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "An unhandled exception occurred: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "An unknown exception occurred." << std::endl;
		return 1;
	}

	return 0;
}
