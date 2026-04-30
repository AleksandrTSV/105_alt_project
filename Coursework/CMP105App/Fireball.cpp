#include "Fireball.h"
#include <iostream>

Fireball::Fireball()
{
    if (!m_fireballTexture.loadFromFile("gfx/fireball_sheet.png"))
        std::cerr << "Failed to load fireball_sheet.png";
    
    m_anim.addFrame({ {0,   0},   {128, 128} });
    m_anim.addFrame({ {128, 0},   {128, 128} });
    m_anim.addFrame({ {0,   128}, {128, 128} });
    m_anim.addFrame({ {128, 128}, {128, 128} });
    m_anim.setFrameSpeed(0.08f);
    m_anim.setLooping(true);

    setTexture(&m_fireballTexture);
    setSize({ 64.0f, 64.0f });
    setCollisionBox({ {8.0f, 8.0f}, {48.0f, 48.0f} });
    setCollider(true);
    setAlive(false);
}

void Fireball::launch(sf::Vector2f position, bool goRight)
{
    setPosition(position);
    m_velocity.x = goRight ? SPEED : -SPEED;
    m_velocity.y = 0;
    m_anim.setFlipped(!goRight);   // if go left - flip 
    m_anim.reset();
    setAlive(true);
}

void Fireball::update(float dt)
{
    if (!isAlive()) return;
    move(m_velocity * dt);


    m_lifetime -= dt;

    if (m_lifetime <= 0.0f)
    {
        setAlive(false);
    }
}
