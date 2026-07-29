#pragma once

#include "Actor.h"

#include <cstddef>
#include <memory>
#include <vector>

namespace nu {
	class Renderer;

	class Scene {
	public:
		Scene() = default;

		void AddActor(std::unique_ptr<Actor> actor);

		void Update(float dt);
		void Draw(const Renderer& renderer) const;

		void RemoveAll();

		std::size_t GetActorCount() const {
			return m_actors.size();
		}

		std::size_t GetPendingActorCount() const {
			return m_pendingActors.size();
		}

		std::vector<std::unique_ptr<Actor>>& GetActors() {
			return m_actors;
		}

		const std::vector<std::unique_ptr<Actor>>&
			GetActors() const {
			return m_actors;
		}

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
		std::vector<std::unique_ptr<Actor>> m_pendingActors;
		void AddPendingActors();
		void RemoveDestroyedActors();
		void CheckCollisions();

	};
}