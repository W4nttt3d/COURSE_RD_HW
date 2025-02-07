#include "Map.h"
#include "WindowHelper.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "ResourceManager.h"

const float Map::TILE_WIDTH = 64;
const float Map::TILE_HEIGHT = 64;
const unsigned Map::MAP_SIZE = 85;

Map::Map()
{
    m_groundTexture = new sf::Texture();
    m_groundRockTexture = new sf::Texture();
    m_treeOakTexture1 = new sf::Texture();
    m_treeOakTexture2 = new sf::Texture();
    m_treeOakTexture3 = new sf::Texture();
    m_treeOakTexture4 = new sf::Texture();
    m_grassTexture = new sf::Texture();
    m_rockTexture = new sf::Texture();
    m_ironTexture = new sf::Texture();
    m_blockTexture = new sf::Texture();

    loadTextures();
    createSprites();
    m_groundSprites.reserve(85);
    m_objectSprites.reserve(85);

    ResourceManager::GetInstance().addResources(m_objectLayer);
}

Map::~Map() 
{
    delete m_groundTexture;
    delete m_groundRockTexture;
    delete m_treeOakTexture1;
    delete m_treeOakTexture2;
    delete m_treeOakTexture3;
    delete m_treeOakTexture4;
    delete m_grassTexture;
    delete m_rockTexture;
    delete m_ironTexture;
    delete m_blockTexture;
}

void Map::loadTextures()
{
    m_groundTexture->loadFromFile("Assets/Soil.png");
    m_groundRockTexture->loadFromFile("Assets/RoughStone.png");
    m_treeOakTexture1->loadFromFile("Assets/TreeOak_1.png");
    m_treeOakTexture2->loadFromFile("Assets/TreeOak_2.png");
    m_treeOakTexture3->loadFromFile("Assets/TreeOak_3.png");
    m_treeOakTexture4->loadFromFile("Assets/TreeOak_4.png");
    m_grassTexture->loadFromFile("Assets/Grass.png");
    m_rockTexture->loadFromFile("Assets/Rock.png");
    m_ironTexture->loadFromFile("Assets/Iron_ore.png");
    m_blockTexture->loadFromFile("Assets/Block.png");
}

const int MAP_SIZE = 85;

void Map::createSprites()
{
    m_groundSprites.clear();
    m_objectSprites.clear();
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            sf::Sprite groundSprite;
            sf::Sprite objectSprite;

            switch (m_groundLayer[y][x])
            {
            case 1:
                groundSprite.setTexture(*m_groundTexture);
                break;
            case 2:
                groundSprite.setTexture(*m_groundRockTexture);
            default:
                break;
            }
            groundSprite.setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
            m_groundSprites.push_back(groundSprite);

            switch (m_objectLayer[y][x]) {
            case 1:
            case 2:
            case 3:
                objectSprite.setTexture(*m_grassTexture);
                break;
            case 4:
                objectSprite.setTexture(*m_treeOakTexture2);
                break;
            case 5:
                objectSprite.setTexture(*m_treeOakTexture3);
                break;
            case 6:
                objectSprite.setTexture(*m_treeOakTexture4);
                break;
            case 7:
                objectSprite.setTexture(*m_treeOakTexture1);
                break;
            case 8:
                objectSprite.setTexture(*m_rockTexture);
                break;
            case 9:
                objectSprite.setTexture(*m_ironTexture);
                break;
            case 10:
                objectSprite.setTexture(*m_blockTexture);
                objectSprite.setColor(sf::Color(144, 188, 251, 100));
                break;
            case 11:
                objectSprite.setTexture(*m_blockTexture);
                objectSprite.setColor(sf::Color(255, 255, 255, 255));
                break;
            case 12:
                objectSprite.setTexture(*m_blockTexture);
                objectSprite.setColor(sf::Color(255, 105, 180, 100));
                break;
            default:
                continue;
            }
            objectSprite.setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
            m_objectSprites.push_back(objectSprite);
        }
    }
}

void Map::draw(sf::RenderWindow* window)
{
    for (const auto& sprite : m_groundSprites)
    {
        window->draw(sprite);
    }
    for (const auto& sprite : m_objectSprites)
    {
        window->draw(sprite);
    }
}

void Map::setObjectLayer(int x, int y, int objectType)
{
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
    {
        m_objectLayer[y][x] = objectType;

        createSprites();
    }
}

int Map::getObjectLayer(int x, int y) const
{
    if (x >= 0 && x < 85 && y >= 0 && y < 85) {
        return m_objectLayer[y][x];
    }
    return -1;
}

bool Map::isTileBlocked(const sf::Vector2u& position) const
{
    const float x = position.x;
    const float y = position.y;

    if (x >= m_objectLayer[0].size() || x < 0)
    {
        assert(false && "Invalid x was passed for the map Check");
        return true;
    }

    if (y >= m_objectLayer.size() || y < 0)
    {
        assert(false && "Invalid y was passed for the map Check");
        return true;
    }

    return m_objectLayer[y][x] != 0 && m_objectLayer[y][x] != 3 && m_objectLayer[y][x] != 12 && m_objectLayer[y][x] != 10 /*&& m_objectLayer[y][x] != 4 && m_objectLayer[y][x] != 5 && m_objectLayer[y][x] != 6 && m_objectLayer[y][x] != 7*/;
}

sf::Vector2f Map::getPositionFromTile(const sf::Vector2u& tile) const 
{
    float tileSize = 64.0f; 
    return sf::Vector2f(tile.x * tileSize + tileSize / 2, tile.y * tileSize + tileSize / 2);
}


sf::Vector2u Map::getTileFromPosition(const sf::Vector2f& position) const
{
    return { static_cast<unsigned>(position.x / TILE_WIDTH), static_cast<unsigned>(position.y / TILE_HEIGHT) };
}

const std::vector<std::vector<int>>& Map::getAllTiles() const
{
    return m_objectLayer;
}

bool Map::isTileInBounds(const sf::Vector2u& tile) const
{
    return tile.x < MAP_SIZE && tile.y < MAP_SIZE;
}

bool Map::isTileResource(const sf::Vector2u& tile) const
{
    int tileValue = getObjectLayer(tile.x, tile.y);

    switch (tileValue)
    {
    case 4:
    case 5:
    case 6: 
    case 7:
        return true;

    case 8:
        return true; 

    case 9:
        return true; 

    default:
        return false; 
    }
}
