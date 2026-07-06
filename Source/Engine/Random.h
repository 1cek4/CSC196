#pragma once

#include <cstdlib>

namespace nu
{
	inline int RandomInt() {
		return rand();
	}
	/*<summary>
	Get random int values [0.max]
	*/
	inline int RandomInt(int max) {
		return rand() % max;
	}


	inline int RandomInt(int min,int max) {
		return min + rand() % max;
	}
}