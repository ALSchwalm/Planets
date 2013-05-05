
#ifndef PLANET_H_
#define PLANET_H_

namespace Planet
{
	class Planet
	{
	public:
		Planet(unsigned int _x, unsigned int _y, const char _letter) :
			x(_x),
			y(_y),
			letter(_letter),
			population(0)
		{}

		unsigned int getX() const {return x;}
		unsigned int getY() const {return y;}

	private:
		const unsigned int x;
		const unsigned int y;
		const char letter;
		unsigned int population;

		/*
		 * How much population can leave a planet in one fleet
		 */
		const unsigned int MAX_EGRESS = 10; //TODO read from config
	};
}

#endif
