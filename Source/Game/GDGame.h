#pragma once
#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Font.h"
#include "Model.h"

enum class GameState {
	StartGame,
	InGame,
	GameOver
};

class GDGame : public nu::Game {
public:
	GDGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(const nu::Renderer& renderer) override;

private:
	void SetupLevel();
	void SpawnPrefab();
	void SpawnCoin();

private:
	nu::Scene m_gdScene;
	Player* m_player = nullptr;

	GameState m_state = GameState::StartGame;

	int m_lives = 3;
	float m_score = 0.0f;

	float m_spawnTimer = 1.5f;
	float m_scrollSpeed = 400.0f;
	float m_groundY = 950.0f;

	float m_coinSpawnTimer = 1.0f;
	float m_coinLiftHeight = 70.0f;

	nu::Model m_playerModel;
	nu::Model m_hazardModel;
	nu::Model m_platformModel;
	nu::Model m_coinModel;

	nu::Font m_font;
	bool m_fontLoaded = false;
};
