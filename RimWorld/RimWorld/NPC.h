#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "Map.h"
#include "MathHelper.h"
#include "ResourceManager.h"

enum class WorkType
{
    HARVEST,
    RESOURCE_TRANSFER
};

class NPC
{
public:
    NPC(const std::string& name);

    void setName(const std::string& name);
    std::string getName() const;
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void assignTaskForHarvest(const sf::Vector2u& resourceTile);
    void assignTaskForTransfer(const sf::Vector2u& fromTiles, const sf::Vector2u& ToTiles);
    bool isFree() const;
    sf::Vector2f getPosition() const;
    Graph buildGraph();
    void setGraph(const Graph& graph);

private:
    void loadTexture();
    void updatePath(Graph& graph);
    sf::Vector2u getNextTileToMove();
    sf::Vector2u convertVertixToMapTile(unsigned vertex) const;
    unsigned convertMapTileToVertix(sf::Vector2u mapTile) const;
    sf::Vector2u findRandomTile() const;
    void moveTo(float dt, const sf::Vector2f& targetPosition, const sf::Vector2f& currentPosition);
    void harvestResource();
    void transferResource();
    std::vector<sf::Vector2u> getTreeTiles(const sf::Vector2u& startTile) const;
    std::vector<sf::Vector2u> getAdjacentTilesforWolking(const sf::Vector2u& tile) const;
    std::vector<sf::Vector2u> getAdjacentTilesforMine(const sf::Vector2u& tile) const;
    void drawPath(sf::RenderWindow& window) const;
    bool arePositionsApproximatelyEqual(const sf::Vector2f& pos1, const sf::Vector2u& pos2, float tolerance = 0.1f);

    sf::Sprite m_sprite;
    sf::Texture* m_texture;
    Graph m_mapGraph;
    std::vector<sf::Vector2u> m_path;
    sf::Vector2u m_spawnPoint;
    sf::Vector2u m_goalTile;
    sf::Vector2u m_goalNextTile;
    WorkType m_currentWorkType;

    std::chrono::steady_clock::time_point m_lastUpdateTime;
    std::chrono::steady_clock::time_point m_pauseStartTime;
    bool m_pathUpdated;
    bool m_inPause;
    bool m_isWaiting;
    bool m_taskAssigned;
    std::string m_name;
};