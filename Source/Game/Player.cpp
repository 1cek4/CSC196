#include "Player.h"
#include "Renderer.h"
#include "engine.h"
#include "Hazard.h"
#include "Platform.h"
#include "Coin.h"

void Player::Update(float dt) {

	if (m_grounded && nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_velocity.y = m_jumpForce;
		m_grounded = false;
	}

	m_velocity.y += m_gravity * dt;

	m_transform.position += m_velocity * dt;
}

void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}

void Player::OnCollision(nu::Actor& other) {
	Hazard* hazard = dynamic_cast<Hazard*>(&other);

	if (hazard != nullptr) {
		m_hit = true;
		return;
	}

	Coin* coin = dynamic_cast<Coin*>(&other);

	if (coin != nullptr) {
		m_coinsCollected++;
		other.Destroy();
	}
}

void Player::CheckPlatforms(const std::vector<std::unique_ptr<nu::Actor>>& actors) {
	if (m_velocity.y < 0.0f) {
		m_grounded = false;
		return;
	}

	float halfW = m_transform.scale.x * 0.5f;
	float halfH = m_transform.scale.y * 0.5f;

	float playerLeft = m_transform.position.x - halfW;
	float playerRight = m_transform.position.x + halfW;
	float playerBottom = m_transform.position.y + halfH;

	m_grounded = false;

	for (auto& actor : actors) {
		Platform* platform = dynamic_cast<Platform*>(actor.get());
		if (platform == nullptr) continue;

		const nu::Transform& pt = platform->GetTransform();

		float pHalfW = pt.scale.x * 0.5f;
		float pHalfH = pt.scale.y * 0.5f;

		float platLeft = pt.position.x - pHalfW;
		float platRight = pt.position.x + pHalfW;
		float platTop = pt.position.y - pHalfH;

		if (
			playerRight > platLeft && playerLeft < platRight &&
			playerBottom >= platTop && playerBottom <= platTop + 40.0f
			) {
			m_transform.position.y = platTop - halfH;
			m_velocity.y = 0.0f;
			m_grounded = true;
			break;
		}
	}
}
