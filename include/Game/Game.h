
#ifndef GAME_H_
#define GAME_H_

#include "Player/AIPlayer.h"
#include "Player/HumanPlayer.h"
#include "Fleet/Fleet.h"
#include "Planet/Planet.h"
#include <vector>
#include <set>

namespace Game
{

	void setup();
	void update();
	void end();

	extern Player::HumanPlayer* player;
	extern std::vector<Player::AIPlayer*> aiPlayers;

	extern std::set<Fleet::Fleet*> fleets;
	extern std::set<Planet::Planet*> planets;

	extern const unsigned int NUM_PLANETS;
	extern const unsigned int NUM_AI_PLAYERS;
	extern const unsigned int PLANET_DENSITY;
	extern const unsigned int MAX_INITIAL_POP;
	extern const unsigned int MIN_INITIAL_POP;
	extern const unsigned int PLAYER_STARTING_POP;
	extern const unsigned int AI_STARTING_POP;
}

#endif
