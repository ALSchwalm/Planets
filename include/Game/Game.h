
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

	extern Player::HumanPlayer* player;
	extern std::vector<Player::AIPlayer*> aiPlayers;

	extern std::set<Fleet::Fleet*> fleets;
	extern std::set<Planet::Planet*> planets;

	const unsigned int NUM_PLANETS = 15;
	const unsigned int NUM_AI_PLAYERS = 1;
	const unsigned int PLANET_DENSITY = 4;
	const unsigned int MAX_INITIAL_POP = 75;
	const unsigned int MIN_INITIAL_POP = 5;
	const unsigned int PLAYER_STARTING_POP = 100;
	const unsigned int AI_STARTING_POP = 100;
}

#endif
