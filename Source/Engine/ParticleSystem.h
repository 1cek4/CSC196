#pragma once

#include "Particle.h"

#include <cstddef>
#include <vector>

namespace nu {
	class Renderer;

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		void Update(float dt);
		void Draw(const Renderer& renderer) const;

		void Emit(
			const Vector2& position,
			const Vector2& velocity,
			const Color& color,
			float lifespan
		);

		void EmitBurst(
			const Vector2& position,
			int count,
			float minSpeed,
			float maxSpeed,
			const Color& color,
			float lifespan
		);

		void Clear();

		std::size_t GetParticleCount() const {
			return m_particles.size();
		}

	private:
		std::vector<Particle> m_particles;
	};
}