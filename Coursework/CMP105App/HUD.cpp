#include "HUD.h"

HUD::HUD()
{
	if (!m_spriteTexture.loadFromFile(m_spritePath))
		std::cerr << "Failed to load ps glyph sprite\n";

	readInSpriteData();

	float posX = 50.f;
	float offsetX = 35.0f;
	std::vector interestedIn = { "Circle", "Square", "Triangle", "Cross" };
	for (std::pair<std::string, sf::IntRect> pair : m_spriteMap)
		// for each pair of string <file_name> to IntRect <position & size>
	{
		if (std::find(interestedIn.begin(), interestedIn.end(), pair.first) == interestedIn.end())
			continue;		// not X/square/triangle/O
		GameObject hudElement;
		hudElement.setTexture(&m_spriteTexture);
		hudElement.setTextureRect(pair.second);
		hudElement.setSize({ 30.f, 30.f });
		hudElement.setPosition({ posX, 450.f });
		posX += offsetX;
		m_HUD_Elements.push_back(hudElement);
	}

	if (!m_tileTexture.loadFromFile("gfx/tilemap.png"))
		std::cerr << "Failed to load tilemap for HUD hearts\n";

	for (int i = 0; i < 3; i++)
	{
		GameObject heart;
		heart.setTexture(&m_tileTexture);
		heart.setTextureRect(HEART_FULL);
		heart.setSize({ 36.f, 36.f });
		// The position will be updated in `update()` relative to the camera
		m_hearts.push_back(heart);
	}
}

void HUD::readInSpriteData()
{
	std::ifstream inData(m_spriteDataPath);

	if (!inData.is_open()) std::cerr << "Failed to open ps glyph data";

	std::string name;
	int x, y, w, h;
	while (inData >> name >> x >> y >> w >> h)
	{
		m_spriteMap[name] = sf::IntRect({ {x, y}, {w, h} });
	}
	inData.close();
}

void HUD::update(sf::RenderWindow& window, int lives)
{
	// We position the HUD in the top-left corner of the camera
	sf::Vector2f topLeft = window.getView().getCenter()
		- sf::Vector2f(window.getView().getSize() * 0.5f);

	for (int i = 0; i < 3; i++)
	{
		m_hearts[i].setPosition({ topLeft.x + 8.f + i * 42.f, topLeft.y + 8.f });
		// A full or empty heart, depending on lives
		if (i < lives)
			m_hearts[i].setTextureRect(HEART_FULL);
		else
			m_hearts[i].setTextureRect(HEART_EMPTY);
	}
}

void HUD::render(sf::RenderWindow& window)
{
	for (GameObject& element : m_HUD_Elements)
	{
		window.draw(element);
	}
}
