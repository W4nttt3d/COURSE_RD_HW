#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "NpcManager.h"
#include "Map.h"

class Tool
{
public:
    Tool();
    void update(const sf::Vector2i& mousePosition, sf::RenderWindow& window, const sf::View& view);
    void draw(sf::RenderWindow& window);
    void placeBuilding(const sf::Vector2f& worldPosition);
    void placeZoning(const sf::Vector2f& worldPosition);
    void setPlacing(bool isPlacing);
    void handleMouseClick(int mouseX, int mouseY, sf::RenderWindow& window, NpcManager& npcManager);
    void setZoning(bool isZoning);

private:
    sf::Sprite m_buildingSprite;
    sf::Texture m_buildingTexture;
    sf::RectangleShape m_zoneIndicator;
    sf::Vector2i m_mousePosition;
    bool m_isPlacing;
    bool m_isZoning;

    void loadTexture();
};
