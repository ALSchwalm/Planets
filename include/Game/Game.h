
#ifndef GAME_H_
#define GAME_H_

#include "Player/AIPlayer.h"
#include "Player/HumanPlayer.h"
#include "Fleet/Fleet.h"
#include <vector>

namespace Game
{

	void setup(unsigned int numAI);

	extern Player::HumanPlayer* player;
	extern std::vector<Player::AIPlayer*> aiPlayers;

	extern std::vector<Fleet::Fleet*> fleets;
}

#endif
