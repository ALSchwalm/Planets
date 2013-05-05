#ifndef BASEPLAYER_H_
#define BASEPLAYER_H_

namespace Player
{
	class BasePlayer
	{
	public:
		BasePlayer(unsigned int _ID);

		float getMovePercent() const {return movePercent;}
		void setMovePercent(float _movePercent) {movePercent = _movePercent;}

		const unsigned int getID() const {return ID;}

	private:
		const unsigned int ID;
		float movePercent;
	};
}

#endif
