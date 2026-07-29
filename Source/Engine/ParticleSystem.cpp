#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"
#include "MathUtils.h"

#include <algorithm>

namespace nu {
	void ParticleSystem::Emit(
		const Vector2& position,
		const Vector2& velocity,
		const Color& color,
		float lifespan
	) {
		Particle particle;
		particle.position = position;
		particle.velocity = velocity;
		particle.color = color;
		particle.lifespan = lifespan;
		particle.age = 0.0f;

		m_particles.push_back(particle);
	}

	void ParticleSystem::EmitBurst(
		const Vector2& position,
		int count,
		float minSpeed,
		float maxSpeed,
		const Color& color,
		float lifespan
	) {
		for (int i = 0; i < count; i++) {
			float angle = (RandomInt(360)) * DegToRad;
			float speed = (float)RandomInt(
				(int)minSpeed,
				(int)maxSpeed
			);

			Vector2 velocity(
				cosf(angle) * speed,
				sinf(angle) * speed
			);

			Emit(position, velocity, color, lifespan);
		}
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			particle.position += (particle.velocity * dt);
			particle.age += dt;
		}

		m_particles.erase(
			std::remove_if(
				m_particles.begin(),
				m_particles.end(),
				[](const Particle& particle) {
					return !particle.IsAlive();
				}
			),
			m_particles.end()
		);
	}

	void ParticleSystem::Draw(const Renderer& renderer) const {
		for (const auto& particle : m_particles) {
			renderer.SetColor(
				static_cast<Uint8>(particle.color.r * 255.0f),
				static_cast<Uint8>(particle.color.g * 255.0f),
				static_cast<Uint8>(particle.color.b * 255.0f)
			);

			renderer.DrawPoint(
				particle.position.x,
				particle.position.y
			);
		}
	}

	void ParticleSystem::Clear() {
		m_particles.clear();
	}
}