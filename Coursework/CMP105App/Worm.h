#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"
#include <iostream>

class Worm :
    public GameObject
{
public:
    Worm();

    void setupPatrol(float leftEdge, float rightEdge);
    void checkEdges(std::vector<GameObject>* tiles);
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
    void knockback(float playerX);

private:
    sf::Texture m_wormTexture;
    Animation m_walk;
    float m_leftPatrol;
    float m_rightPatrol;
    GameObject m_feelerRight;
    GameObject m_feelerLeft;

    bool m_isGrounded = false;

    const float SPEED = 4.0f;
    const float GRAVITY = 50.0f;
    const float KNOCKBACK_X = 8.0f;
    const float KNOCKBACK_Y = -15.0f;
};
