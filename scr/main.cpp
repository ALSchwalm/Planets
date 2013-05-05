
#include "Interface/Interface.h"
#include "Interface/CLI/CLI.h"

int main()
{
	try
	{
		Interface::initialize();

		while(true)
		{
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
		std::cerr << "An unknown exception occured." << std::endl;
		return 1;
	}

	return 0;
}
