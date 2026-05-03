#pragma once
#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Coin.h"
#include "Flag.h"
#include "HUD.h"
#include <algorithm> // for clamp
#include <iostream>


class LevelTwoWithTiles :
    public Scene
{
public:
    LevelTwoWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;
    void onBegin() override;
    void onEnd() override;

private:
    void updateCameraAndBackground();
    void checkAndSetMessages();
    void drawPauseUI();
    void drawGameOverUI();

    TileMap m_tilemap;
    TileMap m_bgtilemap;
    Player m_player;

    Coin m_coin;
    GameObject m_boopBlock;
    bool m_blockUsed = false;
    Flag m_flag;
    HUD m_hud;

    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 432, 432 };

    sf::Text m_alertText;
    sf::Font m_font;
    sf::Texture m_tileTexture;

    sf::Vector2f m_wallPos = { 11 * 72, 5 * 72 };


    std::vector<std::string> m_promptMessages =
    {
        "Oh I'm stuck.\nMaybe I missed\nsomething back there?",
        "I feel so powerful\nalmost like I\ncan double-jump",
        "Press F to end the day"
    };

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

    sf::Vector2f m_cameraTarget;       // where we want to go
    const float CAM_LERP = 5.0f;      // the speed at which the camera follows the player (higher = harder)
    const float CAM_LOOKAHEAD = 100.f;  // pixels ahead
};

