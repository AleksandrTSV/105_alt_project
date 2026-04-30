#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include "Framework/AudioManager.h"


class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
    void setEdges(float left, float right) { m_leftEdge = left; m_rightEdge = right; };
    void setLeverPosition(sf::Vector2f leverPos) { m_leverPosition = leverPos; };
    void setEndGamePosition(sf::Vector2f endPos) { m_endPosition = endPos; };
    bool inLeverRange();
    bool inEndRange();
    bool getLeverPulled() { return m_leverPulled; };
    bool getGameEndTriggered() { return m_gameEndTriggered; };
    void reset();
    void setCanDoubleJump(bool value) { m_canDoubleJump = value; };
    bool canDoubleJump() { return m_canDoubleJump; };
    void setAudio(AudioManager* audio) { m_audio = audio; };

    void setLeverPulled(bool value) { m_leverPulled = value; }
    sf::Vector2f getVelocity() const{ return m_velocity; }

    void loseLife();

private:
    sf::Texture m_dinoTexture;
    Animation* m_currAnim;
    Animation m_idle;
    Animation m_walk;
    Animation m_sprint;
    float m_sprintTimer = 0.f;
    bool m_isGrounded;
    float m_leftEdge;
    float m_rightEdge;
    sf::Vector2f m_leverPosition;
    sf::Vector2f m_endPosition;
    bool m_leverPulled = false;
    bool m_gameEndTriggered = false;
    bool m_canDoubleJump;
    bool m_hasDoubleJumped;
    AudioManager* m_audio;

    int m_lives = 3;
    float m_invincibleTimer = 0.f;
    const float INVINCIBLE_DURATION = 1.5f;
    bool  m_shootRequested = false;
    float m_shootCooldown = 0.f;
    const float SHOOT_COOLDOWN = 2.0f;

    const float SPRINT_COOLDOWN = 2.0f;
    const float SPRINT_SPEED_MULT = 2.5f;
    const float SPEED = 8.0f;
    const float GRAVITY = 70.0f;
    const float JUMP_FORCE = 20.0f;
    const float SPRINT_ANIM_THRESHOLD = 1.2f * SPEED;
    const float ACTIVATE_RANGE_SQUARED = 700.0f;

};

