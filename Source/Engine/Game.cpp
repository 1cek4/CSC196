#include "pch.h"
#include "Game.h"
#include "Scene.h"
#include "Renderer.h"

namespace nu {
	void Game::Draw(
		const Renderer& renderer
	) {
		if (m_scene != nullptr) {
			m_scene->Draw(renderer);
		}
	}

	void Game::Update(float dt) {
		if (m_scene) {
			m_scene->Update(dt);
		}
	}
}