
#include "Interface/Interface.h"
#include "Interface/CLI/CLI.h"

int main()
{
	Interface::initialize();
	Interface::CLI::initialize();

	while(true)
	{
		Interface::refreshView();
		Interface::CLI::handleInput();
	}


	return 0;
}
