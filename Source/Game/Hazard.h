#pragma once
#include "Actor.h"

class Hazard : public nu::Actor {
public:
	Hazard() = default;
	Hazard(float scrollSpeed, const nu::Transform& transform, const nu::Model& model) :
		Actor{ transform, model },
		m_scrollSpeed{ scrollSpeed }
	{
	}

	void Update(float dt) override;

private:
	float m_scrollSpeed = 400.0f;
};
