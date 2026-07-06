#pragma once

namespace nu {
	class Vector2
	{
	public:
		float x, y;
		Vector2(float v) : x(v), y(v) {}
		Vector2(float x, float y) : x(x), y(y) {}

	};
}