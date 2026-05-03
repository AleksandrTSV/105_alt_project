#pragma once
#include "Framework/GameObject.h"

class HeartPickup :
    public GameObject
{
public:
    HeartPickup();
    void update(float dt) override;
    void spawn(sf::Vector2f pos, sf::Texture* tileTex);
    void collisionResponse(GameObject& collider) override;

private:
    const float GRAVITY = 30.0f;
    bool m_isGrounded = false;
};

