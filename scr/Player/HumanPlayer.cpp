#include "Player/HumanPlayer.h"

namespace Player
{
	BasePlayer* humanPlayer = new HumanPlayer(0);


	HumanPlayer::HumanPlayer(unsigned int _ID) :
		BasePlayer(_ID)
	{
	}
}
