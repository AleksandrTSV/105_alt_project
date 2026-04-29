#pragma once
#include "Framework/GameObject.h"

class Fireball :
    public GameObject
{
public:
    Fireball();

    void launch(sf::Vector2f position, int direction);
    void update(float dt) override;
    void render(sf::RenderWindow& window);

private:
    sf::CircleShape m_outer;
    sf::CircleShape m_inner;
    float m_lifetime;

    const float SPEED = 280.0f;
    const float MAX_LIFETIME = 4.0f;
};
