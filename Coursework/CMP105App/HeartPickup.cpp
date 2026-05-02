#include "HeartPickup.h"

HeartPickup::HeartPickup()
{
    // Full heart: row 3, col 5 in tilemap.png
    setTextureRect({ {4 * 19, 2 * 19}, {18, 18} });
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

void HeartPickup::collisionResponse(GameObject& collider)
{
    sf::FloatRect myBox = getCollisionBox();
    sf::FloatRect tileBox = collider.getCollisionBox();
    auto overlap = myBox.findIntersection(tileBox);
    if (!overlap) return;

    if (overlap->size.x < overlap->size.y)
    {
        if (myBox.position.x < tileBox.position.x)
            move({ -overlap->size.x, 0 });
        else
            move({ overlap->size.x, 0 });
    }
    else
    {
        if (myBox.position.y < tileBox.position.y)
        {
            move({ 0, -overlap->size.y });
            m_velocity = { 0, 0 };
            m_isGrounded = true;
        }
        else
        {
            move({ 0, overlap->size.y });
            m_velocity.y = 0;
        }
    }
}