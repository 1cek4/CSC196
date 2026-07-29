#pragma once

#include <fmod.hpp>

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace nu {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();
		void Update();
		void Shutdown();

		bool LoadSound(
			const std::string& name,
			const std::string& filename
		);

		bool LoadSound(const char* filename);

		void PlaySound(const std::string& name);
		void PlaySound(std::size_t index);

		bool HasSound(const std::string& name) const;

		std::size_t GetSoundCount() const {
			return m_sounds.size();
		}

	private:
		bool CreateSound(
			const char* filename,
			FMOD::Sound*& sound
		);

	private:
		FMOD::System* m_audio = nullptr;

		std::vector<FMOD::Sound*> m_sounds;

		std::unordered_map<std::string, std::size_t> m_soundIndexes;
	};
}