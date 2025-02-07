#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class ResourceType
{
    TREE = 7,
    STONE = 8,
    METAL = 9
};

class Resource
{
public:
    Resource(ResourceType type, const std::vector<std::pair<int, int>>& tiles, int quantity);

    ResourceType getType() const;
    sf::Vector2f getPosition2f() const;
    sf::Vector2u getPosition2u() const;
    void draw(sf::RenderWindow& window) const;
    bool isDestroyed() const;
    void destroy();
    std::vector<std::pair<int, int>> getTiles() const;
    int getQuantity() const; 
    void setQuantity(int quantity);
    void setVisible(bool visible);
    bool isVisible() const;
    void setPosition(const sf::Vector2f& position);
    void updateTiles(const std::vector<std::pair<int, int>>& newTiles);
    void setFont(sf::Font* font);


private:
    ResourceType m_type;
    std::vector<std::pair<int, int>> m_tiles;
    sf::Sprite m_sprite;
    sf::Texture* m_texture;
    sf::Text m_text;
    sf::Font* m_font;
    bool m_destroyed = false;
    int m_quantity; 
    bool m_visible;

    void loadTexture();
    void setupText();
};
