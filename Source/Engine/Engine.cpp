#include "pch.h"
#include "Engine.h"

namespace nu {
	Engine engine;

	bool Engine::Initialize() {
		if (!m_renderer.Initialize("Game Engine", 1920, 1080)) {
			return false;
		}

		if (!m_input.Initialize()) {
			m_renderer.Shutdown();
			return false;
		}

		if (!m_audio.Initialize()) {
			m_input.Shutdown();
			m_renderer.Shutdown();
			return false;
		}

		m_time.Reset();

		return true;
	}

	void Engine::Update() {
		m_time.Tick();
		m_input.Update();
		m_audio.Update();
	}

	void Engine::Shutdown() {
		m_audio.Shutdown();
		m_input.Shutdown();
		m_renderer.Shutdown();
	}
}