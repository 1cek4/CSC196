#pragma once
#include "Actor.h"

class Platform : public nu::Actor {
public:
	Platform() = default;
	Platform(const nu::Transform& transform, const nu::Model& model, float scrollSpeed = 0.0f) :
		Actor{ transform, model },
		m_scrollSpeed{ scrollSpeed }
	{
	}

	void Update(float dt) override;

private:
	float m_scrollSpeed = 0.0f;
};
