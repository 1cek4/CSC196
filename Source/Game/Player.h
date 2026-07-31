#pragma once
#include "Actor.h"

#include <vector>
#include <memory>

class Player : public nu::Actor {
public:
	Player() = default;
	Player(float jumpForce, const nu::Transform& transform) : Actor{ transform }, m_jumpForce{ jumpForce } {}
	Player(float jumpForce, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_jumpForce{ jumpForce } {}

	void Update(float dt) override;
	void Draw(const class nu::Renderer& renderer) const override;

	void OnCollision(nu::Actor& other) override;

	void CheckPlatforms(const std::vector<std::unique_ptr<nu::Actor>>& actors);

	bool WasHit() const { return m_hit; }
	void ResetHit() { m_hit = false; }

	int GetCoinsCollected() const { return m_coinsCollected; }
	void ResetCoinsCollected() { m_coinsCollected = 0; }

	void ResetPosition(const nu::Vector2& pos) {
		m_transform.position = pos;
		m_velocity = nu::Vector2{ 0.0f, 0.0f };
		m_grounded = false;
	}

private:
	float m_jumpForce = -700.0f;
	float m_gravity = 1500.0f;

	bool m_grounded = false;
	bool m_hit = false;

	int m_coinsCollected = 0;
};
