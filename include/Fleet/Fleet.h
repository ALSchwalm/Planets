#ifndef FLEET_H_
#define FLEET_H_

namespace Fleet
{
	class Fleet
	{
	public:
		Fleet(unsigned int _x, unsigned int _y) :
			x(_x),
			y(_y),
			population(0)
		{}

		unsigned int getX() const {return x;}
		unsigned int getY() const {return y;}

	private:
		unsigned int x;
		unsigned int y;
		unsigned int population;
	};
}

#endif
