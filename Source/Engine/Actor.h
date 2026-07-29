#pragma once

#include "Transform.h"
#include "Model.h"

namespace nu {
	class Actor {
	public:
		Actor() = default;
		virtual ~Actor() = default;

		Actor(const Transform& transform) :
			m_transform{ transform }
		{
		}

		Actor(
			const Transform& transform,
			const Model& model
		) :
			m_transform{ transform },
			m_model{ model }
		{
		}

		virtual void Update(float dt);

		virtual void Draw(
			const class Renderer& renderer
		) const;

		const Transform& GetTransform() const {
			return m_transform;
		}

		void SetPosition(const Vector2& position) {
			m_transform.position = position;
		}

		void SetRotation(float rotation) {
			m_transform.rotation = rotation;
		}

		void SetScale(float scale) {
			m_transform.scale = scale;
		}

		const Vector2& GetVelocity() const {
			return m_velocity;
		}

		void SetVelocity(const Vector2& velocity) {
			m_velocity = velocity;
		}

		float GetLifespan() const {
			return m_lifespan;
		}

		void SetLifespan(float lifespan) {
			m_lifespan = lifespan;
		}

		float GetDamping() const {
			return m_damping;
		}

		void SetDamping(float damping) {
			m_damping = damping;
		}

		void SetCollisionRadius(float radius) {
			m_collisionRadius = radius;
		}

		float GetCollisionRadius() const {
			return (m_collisionRadius * m_transform.scale.x);
		}

		bool IsColliding(const Actor& other) const;

		bool IsDestroyed() const {
			return m_destroyed;
		}

		virtual void OnCollision(Actor& other) {}

		void Destroy() {
			m_destroyed = true;
		}

	protected:
		Transform m_transform;
		Vector2 m_velocity{ 0.0f, 0.0f };

		float m_damping = 1.0f;
		float m_lifespan = -1.0f;

		float m_collisionRadius = 1.0f;

		bool m_destroyed = false;

		Model m_model;
	};
}