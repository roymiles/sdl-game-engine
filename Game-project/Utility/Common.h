#pragma once

#include <string>

namespace game { namespace utilities {

// This function converts a string into a pseudo-unique integer
inline unsigned int hashCode(std::string s)
{
	return 1;
}

// Round up to nearest multiple of n
inline int roundUp(int numToRound, int multiple)
{
	if (multiple == 0)
		return numToRound;

	int remainder = numToRound % multiple;
	if (remainder == 0)
		return numToRound;

	return numToRound + multiple - remainder;
}

} }