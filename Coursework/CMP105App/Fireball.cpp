#include "Fireball.h"

Fireball::Fireball()
{
    setSize({ 22.0f, 22.0f });
    setCollisionBox({ {0.0f, 0.0f}, {22.0f, 22.0f} });
    setFillColor(sf::Color::Transparent);
    setAlive(false);

    m_outer.setRadius(11.0f);
    m_outer.setFillColor(sf::Color(240, 65, 20));
    m_outer.setOutlineColor(sf::Color(255, 205, 55));
    m_outer.setOutlineThickness(2.0f);

    m_inner.setRadius(5.0f);
    m_inner.setFillColor(sf::Color(255, 230, 90));

    m_lifetime = 0.0f;
}

void Fireball::launch(sf::Vector2f position, int direction)
{
    setAlive(true);
    setPosition(position);
    setVelocity(SPEED * static_cast<float>(direction), 0.0f);
    m_lifetime = MAX_LIFETIME;
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

void Fireball::render(sf::RenderWindow& window)
{
    if (!isAlive()) return;

    m_outer.setPosition(getPosition());
    m_inner.setPosition(getPosition() + sf::Vector2f(6.0f, 6.0f));

    window.draw(m_outer);
    window.draw(m_inner);
}
