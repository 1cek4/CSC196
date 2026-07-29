#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace nu {
	struct Particle {
		Vector2 position;
		Vector2 velocity;
		Color color{ 1.0f, 1.0f, 1.0f };

		float lifespan = 1.0f;
		float age = 0.0f;

		bool IsAlive() const {
			return age < lifespan;
		}
	};
}