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

	inline float RandomFloat() {
		return (float)rand() / (float)RAND_MAX;
	}

	inline float RandomFloat(float max) {
		return RandomFloat() * max;
	}

	inline float RandomFloat(float min, float max) {
		return min + RandomFloat() * (max - min);
	}
}