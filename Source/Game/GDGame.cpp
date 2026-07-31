#include "pch.h"
#include "GDGame.h"
#include "Hazard.h"
#include "Platform.h"
#include "Coin.h"
#include "Renderer.h"
#include "Random.h"
#include "engine.h"
#include "Text.h"

#include <string>
#include <cmath>

bool GDGame::Initialize() {
	m_fontLoaded = m_font.Load("AlphaFlowers.ttf", 48.0f);

	std::vector<nu::Vector2> playerPoints{
		nu::Vector2{ -0.5f, -0.5f },
		nu::Vector2{ 0.5f, -0.5f },
		nu::Vector2{ 0.5f, 0.5f },
		nu::Vector2{ -0.5f, 0.5f },
		nu::Vector2{ -0.5f, -0.5f }
	};
	m_playerModel = nu::Model{ std::vector<nu::Mesh>{ nu::Mesh{ playerPoints, nu::Color{ 0.2f, 1.0f, 0.3f } } } };

	std::vector<nu::Vector2> hazardPoints{
		nu::Vector2{ 0.0f, -0.5f },
		nu::Vector2{ 0.5f, 0.5f },
		nu::Vector2{ -0.5f, 0.5f },
		nu::Vector2{ 0.0f, -0.5f }
	};
	m_hazardModel = nu::Model{ std::vector<nu::Mesh>{ nu::Mesh{ hazardPoints, nu::Color{ 1.0f, 0.0f, 0.0f } } } };

	std::vector<nu::Vector2> platformPoints{
		nu::Vector2{ -0.5f, -0.5f },
		nu::Vector2{ 0.5f, -0.5f },
		nu::Vector2{ 0.5f, 0.5f },
		nu::Vector2{ -0.5f, 0.5f },
		nu::Vector2{ -0.5f, -0.5f }
	};
	m_platformModel = nu::Model{ std::vector<nu::Mesh>{ nu::Mesh{ platformPoints, nu::Color{ 0.6f, 0.6f, 0.6f } } } };

	std::vector<nu::Vector2> coinPoints;
	const int coinSegments = 20;
	for (int i = 0; i <= coinSegments; i++) {
		float angle = (2.0f * 3.14159265f * (float)i) / (float)coinSegments;
		coinPoints.push_back(nu::Vector2{ 0.5f * cosf(angle), 0.5f * sinf(angle) });
	}
	m_coinModel = nu::Model{ std::vector<nu::Mesh>{ nu::Mesh{ coinPoints, nu::Color{ 1.0f, 0.9f, 0.0f } } } };

	SetupLevel();

	return true;
}

void GDGame::SetupLevel() {
	m_gdScene.RemoveAll();

	nu::Transform platformTransform{ nu::Vector2{ 960.0f, m_groundY + 15.0f }, 0.0f, nu::Vector2{ 2000.0f, 30.0f } };
	auto platform = std::make_unique<Platform>(platformTransform, m_platformModel);
	m_gdScene.AddActor(std::move(platform));

	nu::Transform playerTransform{ nu::Vector2{ 300.0f, m_groundY - 20.0f }, 0.0f, nu::Vector2{ 40.0f, 40.0f } };
	auto player = std::make_unique<Player>(-700.0f, playerTransform, m_playerModel);
	player->SetCollisionRadius(0.4f);

	m_player = player.get();

	m_gdScene.AddActor(std::move(player));
}

void GDGame::SpawnPrefab() {
	int type = nu::RandomInt(4);

	float spawnX = 1970.0f;

	if (type == 0) {
		nu::Transform hazardTransform{ nu::Vector2{ spawnX, m_groundY - 15.0f }, 0.0f, nu::Vector2{ 30.0f, 30.0f } };
		auto hazard = std::make_unique<Hazard>(m_scrollSpeed, hazardTransform, m_hazardModel);
		hazard->SetCollisionRadius(0.4f);

		m_gdScene.AddActor(std::move(hazard));
		return;
	}

	float platformWidth = 180.0f;
	float platformHeight = 20.0f;
	float liftHeight = 50.0f;
	float platformY = m_groundY - liftHeight;

	nu::Transform platformTransform{ nu::Vector2{ spawnX, platformY }, 0.0f, nu::Vector2{ platformWidth, platformHeight } };
	auto platform = std::make_unique<Platform>(platformTransform, m_platformModel, m_scrollSpeed);
	m_gdScene.AddActor(std::move(platform));

	if (type == 1) {
		return;
	}

	float spikeY = platformY - (platformHeight * 0.5f) - 15.0f;
	float spikeX = spawnX;

	if (type == 3) {
		spikeX = spawnX + (platformWidth * 0.5f) - 15.0f;
	}

	nu::Transform hazardTransform{ nu::Vector2{ spikeX, spikeY }, 0.0f, nu::Vector2{ 30.0f, 30.0f } };
	auto hazard = std::make_unique<Hazard>(m_scrollSpeed, hazardTransform, m_hazardModel);
	hazard->SetCollisionRadius(0.4f);

	m_gdScene.AddActor(std::move(hazard));
}

void GDGame::SpawnCoin() {
	float spawnX = 1970.0f;

	float liftHeight = nu::RandomFloat(m_coinLiftHeight, m_coinLiftHeight + 120.0f);
	float coinY = m_groundY - liftHeight;

	nu::Transform coinTransform{ nu::Vector2{ spawnX, coinY }, 0.0f, nu::Vector2{ 30.0f, 30.0f } };
	auto coin = std::make_unique<Coin>(m_scrollSpeed, coinTransform, m_coinModel);
	coin->SetCollisionRadius(0.4f);

	m_gdScene.AddActor(std::move(coin));
}

void GDGame::Update(float dt) {
	nu::Input& input = nu::engine.GetInput();

	if (m_state == GameState::StartGame) {
		if (input.GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_state = GameState::InGame;
			nu::engine.GetAudio().PlaySound("bgmusic");
		}

		return;
	}

	if (m_state == GameState::GameOver) {
		if (input.GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_lives = 3;
			m_score = 0.0f;
			m_spawnTimer = 1.5f;
			m_coinSpawnTimer = 1.0f;

			SetupLevel();

			m_state = GameState::InGame;
		}

		return;
	}

	m_spawnTimer -= dt;
	if (m_spawnTimer <= 0.0f) {
		SpawnPrefab();
		m_spawnTimer = nu::RandomFloat(1.2f, 2.2f);
	}

	m_coinSpawnTimer -= dt;
	if (m_coinSpawnTimer <= 0.0f) {
		SpawnCoin();
		m_coinSpawnTimer = nu::RandomFloat(1.5f, 3.0f);
	}

	m_gdScene.Update(dt);

	if (m_player != nullptr) {
		m_player->CheckPlatforms(m_gdScene.GetActors());
	}

	m_score += dt * 10.0f;

	if (m_player != nullptr) {
		int coinsCollected = m_player->GetCoinsCollected();
		if (coinsCollected > 0) {
			m_score += 50.0f * coinsCollected;
			m_player->ResetCoinsCollected();
		}
	}

	if (m_player != nullptr && m_player->WasHit()) {
		m_player->ResetHit();
		m_lives--;

		if (m_lives <= 0) {
			m_state = GameState::GameOver;
		}
		else {
			m_player->ResetPosition(nu::Vector2{ 300.0f, m_groundY - 20.0f });

			for (auto& actor : m_gdScene.GetActors()) {
				if (dynamic_cast<Hazard*>(actor.get()) != nullptr) {
					actor->Destroy();
					continue;
				}

				if (dynamic_cast<Coin*>(actor.get()) != nullptr) {
					actor->Destroy();
					continue;
				}

				Platform* platform = dynamic_cast<Platform*>(actor.get());
				if (platform != nullptr && platform->GetTransform().scale.x < 1000.0f) {
					actor->Destroy();
				}
			}
		}
	}
}

void GDGame::Draw(const nu::Renderer& renderer) {
	nu::Renderer& r = const_cast<nu::Renderer&>(renderer);

	m_gdScene.Draw(renderer);

	if (!m_fontLoaded) {
		return;
	}

	if (m_state == GameState::StartGame) {
		nu::Text startText{ &m_font };
		startText.Create(r, "Press Space to Start", nu::Vector3{ 1.0f, 1.0f, 1.0f });
		startText.Draw(r, 600, 500);

		return;
	}

	if (m_state == GameState::GameOver) {
		nu::Text overText{ &m_font };
		overText.Create(r, "Game Over - Press Space to Restart", nu::Vector3{ 1.0f, 1.0f, 1.0f });
		overText.Draw(r, 300, 500);

		return;
	}

	nu::Text scoreText{ &m_font };
	scoreText.Create(r, "Score: " + std::to_string((int)m_score), nu::Vector3{ 1.0f, 1.0f, 1.0f });
	scoreText.Draw(r, 20, 20);

	nu::Text livesText{ &m_font };
	livesText.Create(r, "Lives: " + std::to_string(m_lives), nu::Vector3{ 1.0f, 1.0f, 1.0f });
	livesText.Draw(r, 20, 70);
}
