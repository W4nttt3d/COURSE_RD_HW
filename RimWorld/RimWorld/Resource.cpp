#include "Resource.h"
#include "NpcManager.h"
#include <iostream>

Resource::Resource(ResourceType type, const std::vector<std::pair<int, int>>& tiles, int quantity)
    : m_type(type), m_tiles(tiles), m_destroyed(false), m_quantity(quantity)
{
    m_texture = new sf::Texture();
    loadTexture();
    /*m_font = new sf::Font();
    setupText();*/


    if (!m_tiles.empty()) {
        sf::Vector2u pos(m_tiles[0].first, m_tiles[0].second);
        sf::Vector2f position(static_cast<float>(pos.x * 64 + 32), static_cast<float>(pos.y * 64 + 32));
        m_sprite.setPosition(position);
        //m_text.setPosition(position.x, position.y + m_sprite.getGlobalBounds().height / 2 + 10); 
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
    setupText();
}

void Resource::setupText()
{
    m_font->loadFromFile("Assets/FixelDisplay-Bold.ttf");

    m_text.setFont(*m_font);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::White);

    m_text.setString(std::to_string(m_quantity));
}

void Resource::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
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
        m_sprite.setColor(sf::Color(255, 255, 255, 0));
    }
    else
    {
        m_sprite.setColor(sf::Color::Transparent);
    }
}

bool Resource::isVisible() const
{
    return m_visible;
}

void Resource::setPosition(const sf::Vector2u& position)
{
    m_sprite.setPosition(position.x, position.y);
    std::cout << m_sprite.getPosition().x << m_sprite.getPosition().y;
    //m_text.setPosition(position.x, position.y + m_sprite.getGlobalBounds().height / 2 + 10);
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
