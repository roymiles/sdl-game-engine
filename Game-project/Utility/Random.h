#pragma once

#include <string>
#include <algorithm>

namespace game { namespace utilities {

// See: https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
inline std::string randomString(size_t length)
{
	auto randChar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t maxIndex = (sizeof(charset) - 1);
		return charset[rand() % maxIndex];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randChar);
	return str;
}

} }