#pragma once
#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Worm.h"
#include "Fireball.h"
#include "Lever.h"
#include "Flag.h"
#include "HeartPickup.h"
#include "HUD.h"
#include <algorithm>

class LevelWithTiles :
    public Scene
{
public:
    LevelWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;
    void onBegin() override;
    void onEnd() override;

private:
    void updateCameraAndBackground();
    void drawPauseUI();
    void drawGameOverUI();

    TileMap m_tilemap;
    TileMap m_bgtilemap;
    Player m_player;
    std::vector<Worm> m_worms;
    std::vector<Fireball> m_fireballs;
    std::vector<HeartPickup> m_heartPickups;
    HUD m_hud;
    sf::Texture m_tileTexture;
    Lever m_lever;
    sf::Text m_alertText;
    sf::Font m_font;
    std::vector<Flag*> m_flags;
    bool m_flagLeverPulled = false;
    float m_promptTimer;

    const float PROMPT_TIME = 2.f;
    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 432, 432 };

    // Pause
    bool m_isPaused = false;
    GameObject m_pauseOverlay;
    sf::Text m_pauseTitle;
    sf::Text m_pauseHint;

    GameObject m_resumeButton;
    sf::Text m_resumeLabel;

    GameObject m_menuButton;
    sf::Text m_menuLabel;

    // Game Over
    bool m_isGameOver = false;
    GameObject m_gameOverOverlay;
    sf::Text   m_gameOverTitle;
    sf::Text   m_gameOverHint;

    // Camera
    sf::Vector2f m_cameraTarget;       // where we want to go
    const float CAM_LERP = 5.0f;      // the speed at which the camera follows the player (higher = harder)
    const float CAM_LOOKAHEAD = 100.f;  // pixels ahead
};

