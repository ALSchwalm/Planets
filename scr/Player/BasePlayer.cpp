
#include "Player/BasePlayer.h"

namespace Player
{
	BasePlayer::BasePlayer(unsigned int _ID) :
			ID(_ID),
			movePercent(50) //TODO read from config
	{
	}

	void BasePlayer::incrementMovePercent()
	{
		if (movePercent+5 < 100)
		{
			movePercent += 5;
		}
		else
		{
			movePercent = 100;
		}
	}
	void BasePlayer::decrementMovePercent()
	{
		if (movePercent > 5)
		{
			movePercent -= 5;
		}
		else
		{
			movePercent = 0;
		}
	}
}
