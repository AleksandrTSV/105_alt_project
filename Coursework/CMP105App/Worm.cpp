#include "Worm.h"

Worm::Worm()
{
    for (int i = 0; i < 6; ++i)
    {
        m_walk.addFrame({ {i * 64, 0}, {64, 64} });
    }
    m_walk.setFrameSpeed(1.0f / 8.0f);

    setSize({ 72.0f, 72.0f });
    setCollisionBox({ {8.0f, 34.0f}, {56.0f, 30.0f} });
    setTextureRect(m_walk.getCurrentFrame());

    m_leftPatrol = 0.0f;
    m_rightPatrol = 0.0f;
    m_startX = 0.0f;
    m_startY = 0.0f;
    m_direction = 1;
}

void Worm::setupPatrol(float leftEdge, float rightEdge)
{
    m_leftPatrol = leftEdge;
    m_rightPatrol = rightEdge;
    m_startX = getPosition().x;
    m_startY = getPosition().y;
}

void Worm::update(float dt)
{
    if (!isAlive()) return;

    move({ SPEED * m_direction * dt, 0.0f });

    if (getPosition().x <= m_leftPatrol)
    {
        setPosition({ m_leftPatrol, getPosition().y });
        m_direction = 1;
    }
    else if (getPosition().x >= m_rightPatrol)
    {
        setPosition({ m_rightPatrol, getPosition().y });
        m_direction = -1;
    }

    m_velocity = { SPEED * static_cast<float>(m_direction), 0.0f };
    m_walk.setFlipped(m_direction < 0);
    m_walk.animate(dt);
    setTextureRect(m_walk.getCurrentFrame());
}

void Worm::reset()
{
    setAlive(true);
    setPosition({ m_startX, m_startY });
    m_direction = 1;
    m_walk.reset();
    setTextureRect(m_walk.getCurrentFrame());
}
