#include "pch.h"
#include "AudioSystem.h"

#include <fmod_errors.h>

#include <iostream>

namespace nu {
	bool AudioSystem::Initialize() {
		FMOD_RESULT result =
			FMOD::System_Create(&m_audio);

		if (result != FMOD_OK) {
			std::cerr
				<< "FMOD System_Create failed: "
				<< FMOD_ErrorString(result)
				<< '\n';

			return false;
		}

		void* extraDriverData = nullptr;

		result = m_audio->init(
			32,
			FMOD_INIT_NORMAL,
			extraDriverData
		);

		if (result != FMOD_OK) {
			std::cerr
				<< "FMOD initialization failed: "
				<< FMOD_ErrorString(result)
				<< '\n';

			m_audio->release();
			m_audio = nullptr;

			return false;
		}

		return true;
	}

	void AudioSystem::Update() {
		if (m_audio != nullptr) {
			m_audio->update();
		}
	}

	void AudioSystem::Shutdown() {
		for (FMOD::Sound* sound : m_sounds) {
			if (sound != nullptr) {
				sound->release();
			}
		}

		m_sounds.clear();
		m_soundIndexes.clear();

		if (m_audio != nullptr) {
			m_audio->close();
			m_audio->release();
			m_audio = nullptr;
		}
	}

	bool AudioSystem::CreateSound(
		const char* filename,
		FMOD::Sound*& sound
	) {
		if (
			m_audio == nullptr ||
			filename == nullptr
			) {
			return false;
		}

		sound = nullptr;

		FMOD_RESULT result = m_audio->createSound(
			filename,
			FMOD_DEFAULT,
			nullptr,
			&sound
		);

		if (result != FMOD_OK) {
			std::cerr
				<< "Could not load "
				<< filename
				<< ": "
				<< FMOD_ErrorString(result)
				<< '\n';

			sound = nullptr;
			return false;
		}

		return true;
	}

	bool AudioSystem::LoadSound(
		const std::string& name,
		const std::string& filename
	) {
		if (name.empty() || filename.empty()) {
			return false;
		}

		if (HasSound(name)) {
			std::cerr
				<< "A sound named '"
				<< name
				<< "' is already loaded.\n";

			return false;
		}

		FMOD::Sound* sound = nullptr;

		if (!CreateSound(filename.c_str(), sound)) {
			return false;
		}

		std::size_t index = m_sounds.size();

		m_sounds.push_back(sound);
		m_soundIndexes[name] = index;

		return true;
	}

	bool AudioSystem::LoadSound(const char* filename) {
		FMOD::Sound* sound = nullptr;

		if (!CreateSound(filename, sound)) {
			return false;
		}

		m_sounds.push_back(sound);

		return true;
	}

	void AudioSystem::PlaySound(
		const std::string& name
	) {
		auto found = m_soundIndexes.find(name);

		if (found == m_soundIndexes.end()) {
			std::cerr
				<< "Could not find sound named '"
				<< name
				<< "'.\n";

			return;
		}

		PlaySound(found->second);
	}

	void AudioSystem::PlaySound(std::size_t index) {
		if (
			m_audio == nullptr ||
			index >= m_sounds.size() ||
			m_sounds[index] == nullptr
			) {
			return;
		}

		FMOD_RESULT result = m_audio->playSound(
			m_sounds[index],
			nullptr,
			false,
			nullptr
		);

		if (result != FMOD_OK) {
			std::cerr
				<< "FMOD playback failed: "
				<< FMOD_ErrorString(result)
				<< '\n';
		}
	}

	bool AudioSystem::HasSound(
		const std::string& name
	) const {
		return (
			m_soundIndexes.find(name) !=
			m_soundIndexes.end()
			);
	}
}