#include "Worm.h"

Worm::Worm()
{
    if (!m_wormTexture.loadFromFile("gfx/worm_sheet.png"))
        std::cerr << "NO WORM TEXTURE";

    for (int i = 0; i < 6; ++i)
    {
        m_walk.addFrame({ {i * 64, 0}, {64, 64} });
    }
    m_walk.setFrameSpeed(1.0f / 8.0f);
    m_walk.setLooping(true);

    setTexture(&m_wormTexture);
    setSize({ 72, 72 });
    setCollisionBox({ {8, 8}, {56, 56} });
    setCollider(true);
    setAlive(true);

    m_velocity.x = SPEED; //go right first
}

void Worm::setupPatrol(float leftEdge, float rightEdge)
{
    m_leftPatrol = leftEdge;
    m_rightPatrol = rightEdge;
}

void Worm::update(float dt)
{
    if (!isAlive()) return;

    is_Grounded = false;

    // Turn at the edges of the patrol zone
    if (getPosition().x <= m_leftPatrol)
    {
        m_velocity.x = SPEED;
        m_walk.setFlipped(false);
    }
    if (getPosition().x + getSize().x >= m_rightPatrol)
    {
        m_velocity.x = -SPEED;
        m_walk.setFlipped(true);
    }

    move(m_velocity);
    m_walk.animate(dt);
    setTextureRect(m_walk.getCurrentFrame());
}

void Worm::collisionResponse(GameObject& collider) 
{

}

void Worm::knockback(float playerX)
{
    float dir = (getPosition().x > playerX) ? 1.f : -1.f;
    m_velocity.x = dir * KNOCKBACK_X;
    m_velocity.y = KNOCKBACK_Y;

    m_walk.setFlipped(dir < 0);
}