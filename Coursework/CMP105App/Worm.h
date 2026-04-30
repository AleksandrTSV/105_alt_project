#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>

class Worm :
    public GameObject
{
public:
    Worm();

    void setupPatrol(float leftEdge, float rightEdge);
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
    void knockback(float playerX);

private:
    sf::Texture m_wormTexture;
    Animation m_walk;
    float m_leftPatrol;
    float m_rightPatrol;
    int m_direction;

    bool is_Grounded = false;

    const float SPEED = 4.0f;
    const float GRAVITY = 50.0f;
    const float KNOCKBACK_X = 8.0f;
    const float KNOCKBACK_Y = -15.0f;
};
