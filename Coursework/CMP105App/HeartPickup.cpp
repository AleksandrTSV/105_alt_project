#include "HeartPickup.h"

HeartPickup::HeartPickup()
{
    // Full heart: row 3, col 5 in tilemap.png
    setTextureRect({ {5 * 19, 3 * 19}, {18, 18} });
    setSize({ 36, 36 });
    setCollisionBox({ {0, 0}, {36, 36} });
    setCollider(true);
    setAlive(false);
    m_velocity.y = -5.f;  // a short jump after spawning
}

void HeartPickup::spawn(sf::Vector2f pos, sf::Texture* tileTex)
{
    setTexture(tileTex);
    setPosition(pos);
    m_velocity.y = -5.f;
    m_isGrounded = false;
    setAlive(true);
}

void HeartPickup::update(float dt)
{
    if (!isAlive()) return;

    if (!m_isGrounded)
        m_velocity.y += GRAVITY * dt;

    move(m_velocity);
}