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
    void reset();

private:
    sf::Texture m_wormTexture;
    Animation m_walk;
    float m_leftPatrol;
    float m_rightPatrol;
    float m_startX;
    float m_startY;
    int m_direction;

    const float SPEED = 80.0f;
};
