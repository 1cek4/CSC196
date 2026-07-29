#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

namespace nu {
	void Actor::Update(float dt) {
		m_transform.position += (m_velocity * dt);
		m_velocity *= m_damping;

		m_transform.position.x = Wrap(0.0f, 1920.0f, m_transform.position.x);
		m_transform.position.y = Wrap(0.0f, 1080.0f, m_transform.position.y);

		if (m_lifespan >= 0.0f) {
			m_lifespan -= dt;
			if (m_lifespan <= 0.0f) {
				Destroy();
			}
		}
	}

	void Actor::Draw(
		const Renderer& renderer
	) const {
		if (!m_destroyed) {
			renderer.DrawModel(
				m_model,
				m_transform
			);
		}
	}

	bool Actor::IsColliding(const Actor& other) const {
		Vector2 delta = m_transform.position - other.m_transform.position;
		float distSqr = delta.LengthSqr();

		float radiusSum = GetCollisionRadius() + other.GetCollisionRadius();
		float radiusSumSqr = radiusSum * radiusSum;

		return distSqr <= radiusSumSqr;
	}
}