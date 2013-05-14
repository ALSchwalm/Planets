#ifndef UTILS_H_
#define UTILS_H_

#include <sstream>

namespace Utils
{
	template<typename T, typename U>
	inline T convert(U u)
	{
		std::stringstream ss;
		T t;
		ss << u;
		ss >> t;
		return t;
	}
}

#endif
