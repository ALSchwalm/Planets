#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_


#include "Player/BasePlayer.h"

namespace Player
{
	class HumanPlayer : public BasePlayer
	{
	public:
		HumanPlayer(unsigned int _ID);

	private:
	};

	extern BasePlayer* humanPlayer;

}

#endif
