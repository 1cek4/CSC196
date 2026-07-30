#pragma once

#include "Input.h"
#include "Renderer.h"
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "GameTime.h"
#include "MathUtils.h"
#include "Transform.h"
#include "Actor.h"
#include "Scene.h"
#include "AudioSystem.h"
#include "File.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "ParticleSystem.h "

namespace nu {
	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Update();
		void Shutdown();

		AudioSystem& GetAudio() {
			return m_audio;
		}

		Input& GetInput() {
			return m_input;
		}

		Renderer& GetRenderer() {
			return m_renderer;
		}

		Time& GetTime() {
			return m_time;
		}

		ParticleSystem& GetPS() { return m_particleSystem; }

		private:
			Input m_input;
			Renderer m_renderer;
			Time m_time;
			AudioSystem m_audio;
			ParticleSystem m_particleSystem;

		};

	extern Engine engine;
}