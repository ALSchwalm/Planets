
#ifndef GAME_H_
#define GAME_H_

#include "Player/AIPlayer.h"
#include "Player/HumanPlayer.h"
#include "Fleet/Fleet.h"
#include "Planet/Planet.h"
#include <vector>

namespace Game
{

	void setup(unsigned int numAI);

	extern Player::HumanPlayer* player;
	extern std::vector<Player::AIPlayer*> aiPlayers;

	extern std::vector<Fleet::Fleet*> fleets;
	extern std::vector<Planet::Planet*> planets;

	const unsigned int NUM_PLANETS = 15;
}

#endif
