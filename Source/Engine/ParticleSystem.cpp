#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"
#include "MathUtils.h"

#include <algorithm>

namespace nu {
	bool ParticleSystem::Initialize(size_t size) {
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (!particle.active) continue;

			particle.lifespan -= dt;
			particle.active = particle.lifespan > 0;

			particle.position += particle.velocity * dt;
		}
	}

	void ParticleSystem::Draw(const Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
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
	}

	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* freeParticle = GetFreeParticle();

		if (freeParticle) {
			*freeParticle = particle;
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active)
				return &particle;
		}

		return nullptr;
	}
}