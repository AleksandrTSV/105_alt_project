#pragma once
#include "Framework/GameObject.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class HUD :
    public GameObject
{

public:
    HUD();
    void render(sf::RenderWindow& window); 
    void update(sf::RenderWindow& window, int lives);

private:
    void readInSpriteData();

    std::vector<GameObject> m_HUD_Elements;
    sf::Texture m_spriteTexture;
    std::string m_spritePath = "gfx/ps_glyphs.png";
    std::string m_spriteDataPath = "data/ps_glyph_data.txt";

    std::map<std::string, sf::IntRect> m_spriteMap;

    // Hearts
    sf::Texture m_tileTexture;
    std::vector<GameObject> m_hearts;

    // IntRect for every type of heart in tilemap.png
    // row=3, col=5 -> full; col=7 -> empty
    const sf::IntRect HEART_FULL = { {5 * 19, 3 * 19}, {18, 18} };
    const sf::IntRect HEART_EMPTY = { {7 * 19, 3 * 19}, {18, 18} };
};

