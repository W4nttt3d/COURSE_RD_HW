#include "Resource.h"
#include "NpcManager.h"
#include <iostream>

Resource::Resource(ResourceType type, const std::vector<std::pair<int, int>>& tiles, int quantity)
    : m_type(type), m_tiles(tiles), m_destroyed(false), m_quantity(quantity)
{
    m_texture = new sf::Texture();
    loadTexture();


    if (!m_tiles.empty()) {
        sf::Vector2u pos(m_tiles[0].first, m_tiles[0].second);
        sf::Vector2f position(static_cast<float>(pos.x * 64 + 32), static_cast<float>(pos.y * 64 + 32));
        m_text.setPosition(position.x - 3, position.y + 11);
        m_sprite.setPosition(position);
    }

    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

ResourceType Resource::getType() const
{
    return m_type;
}


int Resource::getQuantity() const
{
    return m_quantity;
}

void Resource::setQuantity(int quantity)
{
    m_quantity += quantity;
    m_text.setString(std::to_string(m_quantity));

    if (m_quantity <= 0)
    {
        setVisible(false);
        destroy();
        ResourceManager::GetInstance().removeResource(getPosition2u()); 
    }
    else if(m_quantity > 0 && m_visible == false)
    {
        setVisible(true);
    }
}

void Resource::setFont(sf::Font* font)
{
    m_font = font;
    setupText();
}


void Resource::setupText()
{
    m_text.setString(std::to_string(m_quantity));
    m_text.setFont(*m_font);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::White);
}

void Resource::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
    window.draw(m_text);
}

void Resource::loadTexture()
{
    switch (m_type) {
    case ResourceType::TREE:
        m_texture->loadFromFile("Assets/Wood.png");
        break;
    case ResourceType::STONE:
        m_texture->loadFromFile("Assets/Stone.png");
        break;
    case ResourceType::METAL:
        m_texture->loadFromFile("Assets/Iron.png");
        break;
    }
    m_sprite.setTexture(*m_texture);
}

bool Resource::isDestroyed() const
{
    return m_destroyed;
}

void Resource::destroy()
{
    m_destroyed = true; 
}

std::vector<std::pair<int, int>> Resource::getTiles() const
{
    return m_tiles;
}

void Resource::setVisible(bool visible)
{
    m_visible = visible;
    if (visible)
    {
        m_sprite.setColor(sf::Color(255, 255, 255, 255));
        m_text.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else
    {
        m_sprite.setColor(sf::Color(255, 255, 255, 0));
        m_text.setFillColor(sf::Color(255, 255, 255, 0));
    }

    std::cout << "Set visible: " << m_visible << ", Alpha: " << m_sprite.getColor().a << std::endl;
}

bool Resource::isVisible() const
{
    return m_visible;
}

void Resource::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
    std::cout << "Set position: " << position.x << ", " << position.y << std::endl;
    m_text.setPosition(position.x - 3, position.y + 11);
}

sf::Vector2f Resource::getPosition2f() const
{
    return m_sprite.getPosition();
}

sf::Vector2u Resource::getPosition2u() const
{
    if (!m_tiles.empty()) {
        return sf::Vector2u(m_tiles[0].first, m_tiles[0].second);
    }
    return sf::Vector2u(0, 0);
}

void Resource::updateTiles(const std::vector<std::pair<int, int>>& newTiles) 
{
    m_tiles = newTiles;
}