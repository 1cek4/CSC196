#pragma once
#include "Actor.h"

class Coin : public nu::Actor {
public:
	Coin() = default;
	Coin(float scrollSpeed, const nu::Transform& transform, const nu::Model& model) :
		Actor{ transform, model },
		m_scrollSpeed{ scrollSpeed }
	{
	}

	void Update(float dt) override;

private:
	float m_scrollSpeed = 400.0f;
};
