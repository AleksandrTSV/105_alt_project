#pragma once
#include "Framework/GameObject.h"
#include <iostream>
#include <fstream>
#include <map>

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
};

class HUD :
    public GameObject
{
};

