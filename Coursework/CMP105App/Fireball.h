#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Fireball :
    public GameObject
{
public:
    Fireball();

    void launch(sf::Vector2f position, bool goRight);
    void update(float dt) override;

private:
    sf::Texture m_fireballTexture;
    Animation m_anim;
    float m_lifetime;

    const float SPEED = 15.0f;
    const float MAX_LIFETIME = 4.0f;
};
