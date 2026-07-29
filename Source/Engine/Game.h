#pragma once

namespace nu {
	class Scene;
	class Renderer;

	class Game {
	public:
		Game() = default;

		Game(Scene* scene) :
			m_scene{ scene }
		{
		}

		virtual ~Game() = default;

		virtual bool Initialize() {
			return true;
		}

		virtual void Shutdown() {}

		virtual void Draw(
			const Renderer& renderer
		);

		virtual void Update(float dt);

		void SetScene(Scene* scene) {
			m_scene = scene;
		}

	protected:
		Scene* m_scene{ nullptr };
	};
}