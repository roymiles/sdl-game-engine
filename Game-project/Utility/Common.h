#pragma once

#include <string>

namespace game { namespace utilities {

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
// This function converts a string into a pseudo-unique integer
// See: https://stackoverflow.com/questions/8317508/hash-function-for-a-string
inline unsigned hashCode(const char* s)
{
	unsigned h = FIRSTH;
	while (*s) {
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h; // or return h % C;
}

} }