#include "pch.h"
#include "Scene.h"
#include "Renderer.h"

#include <algorithm>
#include <utility>

namespace nu {
	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		if (actor != nullptr) {
			m_pendingActors.push_back(
				std::move(actor)
			);
		}
	}

	void Scene::AddPendingActors() {
		for (auto& actor : m_pendingActors) {
			m_actors.push_back(
				std::move(actor)
			);
		}

		m_pendingActors.clear();
	}

	void Scene::RemoveDestroyedActors() {
		m_actors.erase(
			std::remove_if(
				m_actors.begin(),
				m_actors.end(),
				[](const std::unique_ptr<Actor>& actor) {
					return (
						actor == nullptr ||
						actor->IsDestroyed()
						);
				}
			),
			m_actors.end()
		);
	}

	void Scene::CheckCollisions() {
		for (std::size_t i = 0; i < m_actors.size(); i++) {
			auto& a = m_actors[i];
			if (a == nullptr || a->IsDestroyed()) continue;

			for (std::size_t j = i + 1; j < m_actors.size(); j++) {
				auto& b = m_actors[j];
				if (b == nullptr || b->IsDestroyed()) continue;

				if (a->IsColliding(*b)) {
					a->OnCollision(*b);
					b->OnCollision(*a);
				}
			}
		}
	}

	void Scene::Update(float dt) {
		AddPendingActors();

		for (auto& actor : m_actors) {
			if (
				actor != nullptr &&
				!actor->IsDestroyed()
				) {
				actor->Update(dt);
			}
		}
		CheckCollisions();
		RemoveDestroyedActors();
	}


	void Scene::RemoveAll() {
		m_pendingActors.clear();
		m_actors.clear();
	}

	void Scene::Draw(const Renderer& renderer) const {
		for (const auto& actor : m_actors) {
			if (
				actor != nullptr &&
				!actor->IsDestroyed()
				) {
				actor->Draw(renderer);
			}
		}
	}

}