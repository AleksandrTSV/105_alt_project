#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>

class Fireball :
    public GameObject
{
public:
    Fireball();

    void launch(sf::Vector2f position, bool goRight);
    void update(float dt) override;

private:
    static sf::Texture m_fireballTexture;
    static bool m_textureLoaded;
    Animation m_anim;
    float m_lifetime = 0.f;

    const float SPEED = 300.0f;
    const float MAX_LIFETIME = 4.0f;
};
