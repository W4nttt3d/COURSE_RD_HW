#include "Tool.h"

Tool::Tool() : m_isPlacing(false), m_isZoning(false)
{
    loadTexture();
    m_buildingSprite.setTexture(m_buildingTexture);
    sf::FloatRect bounds = m_buildingSprite.getLocalBounds();
    m_buildingSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    m_zoneIndicator.setSize(sf::Vector2f(64.f, 64.f));
    m_zoneIndicator.setFillColor(sf::Color(255, 105, 180, 100));
    m_zoneIndicator.setOutlineColor(sf::Color(255, 105, 180));
    m_zoneIndicator.setOutlineThickness(2.f);
}

void Tool::setZoning(bool isZoning)
{
    m_isZoning = isZoning;
}

void Tool::loadTexture()
{
    m_buildingTexture.loadFromFile("Assets/Block.png");
}

void Tool::update(const sf::Vector2i& mousePosition, sf::RenderWindow& window, const sf::View& view)
{
    if (m_isPlacing)
    {
        m_buildingSprite.setColor(sf::Color(144, 188, 251, 100));

        sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition, view);

        int x = static_cast<int>(worldPosition.x) / 64;
        int y = static_cast<int>(worldPosition.y) / 64;
        float offsetX = static_cast<float>(x * 64 + 32);
        float offsetY = static_cast<float>(y * 64 + 32);

        m_buildingSprite.setPosition(offsetX, offsetY);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            placeBuilding(worldPosition);
        }
    }
    else if (m_isZoning)
    {
        sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition, view);
        int x = static_cast<int>(worldPosition.x) / 64;
        int y = static_cast<int>(worldPosition.y) / 64;

        m_zoneIndicator.setPosition(x * 64, y * 64);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            placeZoning(worldPosition);
        }
    }
}

void Tool::draw(sf::RenderWindow& window)
{
    if (m_isPlacing)
    {
        window.draw(m_buildingSprite);
    }
    if (m_isZoning)
    {
        window.draw(m_zoneIndicator);
    }
}

void Tool::placeBuilding(const sf::Vector2f& worldPosition)
{
    int x = static_cast<int>(worldPosition.x) / 64;
    int y = static_cast<int>(worldPosition.y) / 64;

    if (x >= 0 && x < 85 && y >= 0 && y < 85)
    {
        Map::GetInstance().setObjectLayer(x, y, 10);
    }
}

void Tool::placeZoning(const sf::Vector2f& worldPosition)
{
    int x = static_cast<int>(worldPosition.x) / 64;
    int y = static_cast<int>(worldPosition.y) / 64;

    if (x >= 0 && x < 85 && y >= 0 && y < 85)
    {
        Map::GetInstance().setObjectLayer(x, y, 12); 
    }
}

void Tool::setPlacing(bool isPlacing)
{
    m_isPlacing = isPlacing;
}

void Tool::handleMouseClick(int mouseX, int mouseY, sf::RenderWindow& window, NpcManager& npcManager)
{
    sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY));
    sf::Vector2u tile = Map::GetInstance().getTileFromPosition(worldPosition);

    int objectType = Map::GetInstance().getObjectLayer(tile.x, tile.y);

    if (objectType == 8 || objectType == 9 || (objectType >= 4 && objectType <= 7))
    {
        npcManager.assignHarvestTask(tile);
    }
}