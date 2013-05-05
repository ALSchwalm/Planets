
#include "Game/Game.h"

namespace Game
{
	Player::HumanPlayer* player = nullptr;
	std::vector<Player::AIPlayer*> aiPlayers;
	std::vector<Fleet::Fleet*> fleets;

	void setup(unsigned int numAI)
	{
		Game::player = new Player::HumanPlayer(0);
		for (unsigned int ID=1; ID < numAI+1; ++ID)
		{
			aiPlayers.push_back(new Player::AIPlayer(ID));
		}

	}
}
