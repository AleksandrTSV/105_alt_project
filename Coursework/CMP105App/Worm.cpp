#include "Worm.h"

sf::Texture Worm::m_wormTexture;
bool Worm::m_textureLoaded = false;

Worm::Worm()
{
    if (!m_textureLoaded)
    {
        if (!m_wormTexture.loadFromFile("gfx/worm_sheet.png"))
            std::cerr << "NO WORM TEXTURE\n";
        m_textureLoaded = true;
    }

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

    //For the checking if the worm is near the edge
    m_feelerRight.setSize({ 4, 4 });
    m_feelerRight.setCollisionBox({ {0, 0}, {4, 4} });
    m_feelerLeft.setSize({ 4, 4 });
    m_feelerLeft.setCollisionBox({ {0, 0}, {4, 4} });

    m_velocity.x = SPEED; //go right first
}

void Worm::setupPatrol(float leftEdge, float rightEdge)
{
    m_leftPatrol = leftEdge;
    m_rightPatrol = rightEdge;
}

void Worm::checkEdges(std::vector<GameObject>* tiles)
{
    if (!isAlive()) return;

    // Position the tentacles just below the legs and at the edges of the worm
    sf::Vector2f pos = getPosition();
    sf::Vector2f size = getSize();

    // The right tentacle — under the right edge, 4px below the bottom
    m_feelerRight.setPosition({ pos.x + size.x - 4, pos.y + size.y + 2 });
    // The left tentacle – beneath the left edge
    m_feelerLeft.setPosition({ pos.x, pos.y + size.y + 2 });

    bool groundRight = false;
    bool groundLeft = false;

    for (auto& tile : *tiles)
    {
        if (!tile.isCollider()) continue;
        if (Collision::checkBoundingBox(m_feelerRight, tile)) groundRight = true;
        if (Collision::checkBoundingBox(m_feelerLeft, tile)) groundLeft = true;
    }

    // Let’s go right, but there’s a cliff on the right — we’ll have to turn back
    if (m_velocity.x > 0 && !groundRight)
    {
        m_velocity.x = -SPEED;
        m_walk.setFlipped(true);
    }
    // Same on the left
    if (m_velocity.x < 0 && !groundLeft)
    {
        m_velocity.x = SPEED;
        m_walk.setFlipped(false);
    }
}

void Worm::update(float dt)
{
    if (!isAlive()) return;

    move({ m_velocity.x, 0 });
    m_walk.animate(dt);
    setTextureRect(m_walk.getCurrentFrame());
}

void Worm::collisionResponse(GameObject& collider) 
{
    sf::FloatRect myBox = getCollisionBox();
    sf::FloatRect tileBox = collider.getCollisionBox();
    auto overlap = myBox.findIntersection(tileBox);
    if (!overlap) return;

    if (overlap->size.x < overlap->size.y)
    {
        if (myBox.position.x < tileBox.position.x)
        {
            move({ -overlap->size.x, 0 });
            m_velocity.x = -SPEED;
            m_walk.setFlipped(true);
        }
        else
        {
            move({ overlap->size.x, 0 });
            m_velocity.x = SPEED;
            m_walk.setFlipped(false);
        }
    }

}

void Worm::knockback(float playerX)
{
    float dir = (getPosition().x > playerX) ? 1.f : -1.f;
    m_velocity.x = dir * KNOCKBACK_X;
    m_velocity.y = KNOCKBACK_Y;

    m_walk.setFlipped(dir < 0);
}