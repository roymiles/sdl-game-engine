#pragma once

#include <string>
#include <algorithm>
#include <random>
#include <sstream>      // std::stringstream

namespace game { namespace utilities {

// See: https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
inline std::string randomString(size_t length)
{
	//auto randChar = []() -> char
	//{
	//	const char charset[] =
	//		"0123456789"
	//		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	//		"abcdefghijklmnopqrstuvwxyz";
	//	const size_t maxIndex = (sizeof(charset) - 1);
	//	return charset[2 % maxIndex];
	//};
	//std::string str(length, 0);
	//std::generate_n(str.begin(), length, randChar);
	//return str;

	const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	const size_t maxIndex = (sizeof(charset) - 1);

	std::stringstream ss;

	for (int i = 0; i < length; i++)
	{
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, maxIndex); // distribution in range [0, naxIndex]

		ss << charset[dist6(rng)];
	}
	
	return ss.str();
}

} }
