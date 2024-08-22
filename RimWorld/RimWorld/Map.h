#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "WindowHelper.h"

class Map {
public:
    using TilesMapType = std::vector<std::vector<int>>;

    static Map& GetInstance()
    {
        static Map map;
        return map;
    }

    Map();
    ~Map();

    void draw(sf::RenderWindow* window);
    int getObjectLayer(int x, int y) const;
    void loadTextures();
    void createSprites();
    void setObjectLayer(int x, int y, int objectType);

    bool isTileBlocked(const sf::Vector2u& position) const;
    sf::Vector2f getPositionFromTile(const sf::Vector2u& tile) const;
    sf::Vector2u getTileFromPosition(const sf::Vector2f& position) const;
    const std::vector<std::vector<int>>& getAllTiles() const;
    bool isTileInBounds(const sf::Vector2u& tile) const;
    bool isTileResource(const sf::Vector2u& tile) const;


    static const float TILE_WIDTH;
    static const float TILE_HEIGHT;
    static const unsigned MAP_SIZE;

private:
    TilesMapType m_groundLayer = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,2,2,2,2,2,2,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,2,2,2,2,2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    TilesMapType m_objectLayer = {
    {7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3},
    {5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,0,3,3,3,5,4,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,0,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,0,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,7,6,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,7,6,3,3,3,3,3,0,0,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,5,4,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,0,0,0,0,3,3,3,3,3,3,0,3,3,3,7,6,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,7,6,3,3,3,3,3,3,0,3,3,3,5,4,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,5,4,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,0,0,0,0,3,0,3,3,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,0,3,3,3,0,3,3,3,3,3,3,3,7,6,3,3,3,0,3,0,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,3,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,7,6,3,3,3,3,3,0,3,3,3,3,0,3,3,3,3,3,3,3,5,4,3,3,3,0,0,3,3,3,3,3,0,0,0,3,3,3,3,0,0,3,3,3,3,3,0,3,3,3,3,3,3,3,0,0,0,0,3,3},
    {3,3,3,3,3,7,6,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,0,3,3,3,3,3,0,3,3,0,0,3,3,3,3,3,0,0,0,0,3,3,3,3,3,0,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,0,3,3,3,3,3,0,0,0,0,0,3,3},
    {3,3,3,3,3,5,4,3,3,5,4,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,3,3,0,0,3,3,3,3,0,0,0,0,3,3,3,3,3,0,0,3,0,3,3,3,3,3,0,3,3,3,3,7,6,3,0,3,3,3,0,0,3,0,3,3,3,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,7,6,3,3,3,3,0,3,3,3,3,3,3,3,0,3,3,0,3,3,3,0,0,0,0,3,0,0,0,3,3,3,0,3,3,0,3,3,3,3,3,0,0,0,3,3,5,4,3,3,0,3,0,0,3,0,3,3,3,3,3,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,5,4,3,3,3,0,3,3,3,3,7,6,3,3,0,3,3,0,0,0,0,3,0,0,3,3,3,3,0,0,3,3,3,3,0,3,3,3,3,3,3,0,3,0,0,0,3,3,3,3,0,3,0,3,3,0,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,7,6,3,3,3,0,3,3,0,0,3,3,3,3,5,4,3,3,0,3,0,3,0,3,3,0,0,3,3,3,3,3,3,3,0,3,7,6,0,3,3,3,7,6,3,0,3,3,3,0,0,3,3,3,3,0,3,3,0,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,3,0,3,3,3,3,3,3,3,3,7,6,3,3,3,0,3,5,4,0,3,3,3,5,4,3,0,3,3,3,3,0,0,0,0,3,0,3,3,0,3,3,3,3,3,7,6},
    {3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,0,0,0,3,3,3,0,3,3,3,3,5,4,3,3,0,3,3,3,0,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,5,4},
    {3,3,3,3,3,5,4,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,0,0,3,3,3,3,0,0,3,3,3,3,3,3,0,3,3,3,3,0,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,0,0,3,3,3,3,3,0,3,3,3,3,3,0,3,3,3,3,0,3,3,3,3,3,0,3,3,0,3,3,3,3,3,7,6,3,3,3,3,0,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,9,9,9,3,3,3,3,0,0,0,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,3,3,3,3,3,5,4,3,3,3,3,0,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,9,9,9,9,9,3,3,3,3,3,0,0,3,3,3,3,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,9,9,9,9,9,9,9,3,3,3,3,0,3,3,3,3,0,3,0,0,0,0,0,0,0,0,0,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,5,4,3,3,3,3,7,6,3,3,3,3,0,0,3,3,3,3,9,9,9,9,9,9,9,3,3,3,3,0,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,0,0,3,3,3,3,9,9,9,9,9,9,9,3,3,3,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,7,6,3,3,0,3,0,0,0,0,0,0,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,0,3,0,3,3,3,3,9,9,9,9,9,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,5,4,3,3,3,3,7,6,3,3,3,5,4,3,0,0,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,7,6,3,7,6,3,0,0,3,3,0,3,3,0,3,3,3,3,9,9,9,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,5,4,3,5,4,3,3,3,0,0,0,3,3,3,0,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,7,6,3,3,3,3,3,3,5,4,3,3,3,3,3,5,4,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,0,0,3,3,3,3,0,3,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,5,4,3,3,3,3,3,3,3,3,7,6,3,3,3,3,7,6,3,3,5,4,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,0,3,0,3,3,3,3,0,3,3,3,3,3,3,0,0,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,7,6,5,4,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,7,6,3,7,6,3,3,3,3,3,3,3,3,5,4,3},
    {3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,0,3,3,0,0,0,0,3,0,3,3,3,0,0,0,3,0,3,0,3,3,3,3,3,3,3,3,3,7,6,3,5,4,3,3,3,7,6,3,3,3,3,3,3,3,3,7,6,3,3,3,3,5,4,3,5,4,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,0,3,3,3,3,3,3,0,0,0,3,0,3,3,0,0,3,3,0,3,3,7,6,3,3,7,6,3,5,4,3,3,3,3,3,3,5,4,3,3,3,3,7,6,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,0,3,3,7,6,3,3,3,3,0,0,0,0,0,3,3,3,3,0,3,3,5,4,3,3,5,4,3,3,3,3,3,7,6,3,3,3,3,3,3,7,6,5,4,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,5,4,3,3,3,3,3,7,6,3,3,0,3,3,5,4,3,3,3,3,0,0,0,0,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,7,6,3,5,4,3,3,7,6,3,3,5,4,3,3,3,3,3,3,3,3,3,7,6,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,7,6,3,3,5,4,3,3,0,3,3,3,3,3,3,3,3,3,0,3,3,3,0,3,3,3,0,3,3,7,6,3,3,3,3,3,3,5,4,3,3,3,3,3,5,4,3,3,3,3,3,3,7,6,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,0,3,3,3,3,3,3,3,3,0,0,3,3,3,3,0,3,3,0,3,3,3,5,4,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,0,3,0,3,3,3,3,3,3,5,4,7,6,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,0,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,9},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,0,0,3,3,3,3,3,3,3,7,6,3,3,3,3,0,3,3,3,3,3,7,6,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,8,8,8,8},
    {3,3,3,3,3,3,7,6,3,3,3,3,3,7,6,3,3,0,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,0,3,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,7,6,3,5,4,3,7,6,3,3,3,3,5,4,3,7,6,3,3,3,3,3,3,3,8,8,8,8,8},
    {7,6,3,3,7,6,5,4,3,3,3,3,3,5,4,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,7,6,3,3,5,4,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,0,8,8,8,8,8},
    {5,4,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,7,6,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,5,4,7,6,3,3,3,3,3,3,5,4,7,6,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8},
    {3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,5,4,3,3,3,3,3,3,3,3,5,4,3,3,7,6,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8},
    {3,3,7,6,3,7,6,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,7,6,3,3,3,7,6,3,7,6,3,3,3,3,3,3,3,3,3,8,8,8,8,8,8},
    {3,3,5,4,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,7,6,3,3,7,6,3,3,3,3,3,7,6,3,3,5,4,3,3,3,5,4,3,5,4,3,3,3,3,3,3,3,3,3,8,8,9,8,8,8},
    {3,3,3,3,7,6,3,3,3,7,6,3,3,3,3,7,6,3,3,3,3,7,6,3,3,3,3,5,4,3,3,3,3,3,3,7,6,3,3,7,6,3,3,3,3,5,4,3,3,5,4,3,3,0,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,9,9,8,0},
    {7,6,3,3,5,4,3,3,3,5,4,3,7,6,3,5,4,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,7,6,3,3,7,6,3,3,7,6,3,7,6,3,7,6,3,3,3,3,3,0,8,9,9,8,0},
    {5,4,3,7,6,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,7,6,3,3,0,3,3,5,4,3,3,5,4,3,3,5,4,3,5,4,3,5,4,3,3,3,3,3,3,8,8,9,0,0},
    {3,3,3,5,4,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,0,0,3},
    {3,3,7,6,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,0,3,3,3,3,8,8,0,3,3},
    {3,3,5,4,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,0,0,3,3,3,3,5,4,3,3,3,3,0,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,7,6,3,3,3,3,5,4,3,3,3,3,5,4,3,3,3,3,3,7,6,3,3,7,6,3,7,6,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,7,6,3,3,5,4,3,3,3,3,3,0,3,3,7,6,3,3,7,6,3,3,0,3,3,3,3,3,3,3,3,3},
    {3,7,6,3,7,6,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,5,4,3,5,4,3,3,3,3,3,3,3,3,3,3,3,5,4,3,7,6,3,3,5,4,3,3,3,3,3,3,7,6,3,0,3,3,5,4,3,3,5,4,3,3,0,3,3,3,3,3,3,3,3,3},
    {3,5,4,3,5,4,3,7,6,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,7,6,3,5,4,3,3,3,3,3,3,3,3,3,3,5,4,3,0,3,3,3,3,3,7,6,3,3,0,3,3,3,3,3,7,6,3,3,3},
    {3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,5,4,3,3,3,3,7,6,3,3,3,3,3,3,3,7,6,3,3,3,3,3,5,4,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,7,6,3,5,4,3,3,0,3,3,3,3,3,5,4,3,3,3},
    {3,3,3,7,6,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,7,6,3,7,6,3,5,4,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,5,4,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,7,6,3,3,7,6,3,3,3,3,3,3,3,7,6,3,3,5,4,3,3,5,4,3,5,4,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,7,6},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,7,6,3,3,5,4,3,3,5,4,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,0,3,3,3,3,3,3,3,3,5,4},
    {3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,7,6,3,3,3,7,6,3,3,3,3,3,3,0,0,0,0,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,5,4,3,3,3,3,0,3,3,7,6,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,5,4,3,3,3,5,4,3,3,3,3,3,3,0,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,7,6,3,3,7,6,3,0,3,3,3,3,3,3,3,3,3,0,3,3,5,4,3,3,7,6,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,7,6,3,3,3,5,4,3,3,5,4,3,0,7,6,3,3,3,3,3,3,3,0,3,3,3,3,3,3,5,4,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,7,6,3,3,3,3,3,0,8,8,8,8,8,0,0,0,0,0,0,0,3,3,5,4,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,0,5,4,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,5,4,3,3,3,3,0,9,9,9,8,8,8,8,8,8,8,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,0,0,3,0,3,7,6,3,3,7,6,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,9,9,9,8,8,8,8,8,8,8,8,8,0,0,3,3,3,3,7,6,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,0,3,3,3,0,3,5,4,3,3,5,4,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,0,8,8,8,9,9,9,8,8,8,8,8,8,8,8,0,0,3,3,3,3,5,4,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,0,3,3,3,3,0,3,3,3,3,3,3,3,3,3,7,6},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,5,4,3,3,3,3,3,0,0,0,8,8,9,9,9,9,8,8,8,8,8,8,8,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,5,4},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,0,0,0,0,0,0,8,8,9,9,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,0,3,3,3,3,3,0,3,3,3,3,3,7,6,3,3,3,3,3},
    {3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,8,8,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,0,3,3,3,3,3,5,4,3,3,3,7,6},
    {3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,0,0,8,8,8,8,8,8,8,8,8,8,9,9,8,8,8,3,3,3,3,3,7,6,3,3,5,4,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,5,4},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,9,8,8,0,8,8,8,8,8,8,8,8,8,8,9,9,9,8,8,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,9,9,8,8,0,8,8,8,8,8,8,8,8,8,8,9,9,9,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,9,9,8,8,0,8,8,8,9,8,8,8,0,0,8,8,9,9,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,8,8,9,9,8,8,0,0,8,8,9,8,8,8,0,0,8,8,9,9,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,0,0,3,3,3,3,3,0,3,3,3,3,3,3,3,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,8,9,9,8,0,0,0,8,8,9,9,8,8,0,3,3,8,9,9,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,3,3,3,3,0,3,3,0,0,0,0,0,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,9,8,3,3,0,0,8,8,9,9,8,0,3,3,3,3,8,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,9,9,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,0,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,0,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,5,4,3,3,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,7,6,3,3,3,3,3,3,5,4,3,3,7,6,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,0,0,3,3,3,7,6,3,3},
    {3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,0,0,3,3,3,5,4,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,7,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,6,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,7,6,3,3,7,6,3,3,3,0,3,3,3,3,3,3,3,7,6,3,3,3,0,3,3,0,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,5,4,3,3,3,0,3,3,3,3,3,3,3,5,4,3,3,3,0,3,0,0,3,3,3,3,3,3,3,3}
    };
    std::vector<sf::RectangleShape> m_tilesShapes;
    std::vector<sf::Sprite> m_groundSprites;
    std::vector<sf::Sprite> m_objectSprites;
    sf::Texture* m_groundTexture; 
    sf::Texture* m_groundRockTexture;
    sf::Texture* m_treeOakTexture1;   
    sf::Texture* m_treeOakTexture2;
    sf::Texture* m_treeOakTexture3;
    sf::Texture* m_treeOakTexture4;
    sf::Texture* m_grassTexture;  
    sf::Texture* m_rockTexture;  
    sf::Texture* m_ironTexture;  
    sf::Texture* m_blockTexture;
};
