#include "NPC.h"
#include "Map.h"
#include <cmath>
#include <iostream>
#include "Resource.h"
#include "NpcManager.h"

constexpr int RESOURCE_TYPE_TREE = 4;
constexpr int RESOURCE_TYPE_STONE = 8;
constexpr int RESOURCE_TYPE_IRON = 9;

NPC::NPC(const std::string& name) : m_name(name), m_mapGraph(buildGraph()), m_pathUpdated(true), m_inPause(false) {
    m_texture = new sf::Texture();
    loadTexture();
    m_sprite.setTexture(*m_texture);
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    m_sprite.setScale(0.9f, 0.9f);

    m_spawnPoint = findRandomTile();
    m_sprite.setPosition(Map::GetInstance().getPositionFromTile(m_spawnPoint));

    m_goalTile = findRandomTile();

    m_lastUpdateTime = std::chrono::steady_clock::now();
    m_pauseStartTime = std::chrono::steady_clock::now();
    m_isWaiting = false;
    m_taskAssigned = false;
}

void NPC::setName(const std::string& name) {
    m_name = name;
}

std::string NPC::getName() const {
    return m_name;
}

void NPC::update(float dt)
{
    sf::Vector2f currentPosition = m_sprite.getPosition();
    sf::Vector2u currentTile = Map::GetInstance().getTileFromPosition(currentPosition);

    if (m_isWaiting)
    {
        if (m_taskAssigned)
        {
            m_isWaiting = false;
        }
        else
        {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<float> pauseElapsedTime = now - m_pauseStartTime;
            if (pauseElapsedTime.count() >= 5.0f)
            {
                m_isWaiting = false;
                m_goalTile = findRandomTile();
                m_lastUpdateTime = now;
            }
        }
    }
    else
    {
        if (currentTile == m_goalTile)
        {
            if (m_taskAssigned)
            {
                if (m_currentWorkType == WorkType::HARVEST)
                {
                    std::cout << "work " << m_name << std::endl;
                    std::cout << currentTile.x << " " << currentTile.y << std::endl;
                    std::cout << m_goalTile.x << " " << m_goalTile.y << std::endl;
                    harvestResource();
                }
                else if (m_currentWorkType == WorkType::RESOURCE_TRANSFER)
                {
                    if (currentTile == m_goalNextTile)
                    {
                        transferResource();
                    }
                    else
                    {
                        std::vector<Resource>& resources = ResourceManager::GetInstance().m_newResources;
                        for (auto& resource : resources)
                        {
                            if (resource.getPosition2u() == m_goalTile)
                            {
                                resource.setVisible(false);
                                m_goalTile = m_goalNextTile;
                                resource.setPosition(m_goalNextTile);
                            }
                        }
                    }
                }
            }
            else
            {
                m_goalTile = findRandomTile();
                m_isWaiting = true;
                m_pauseStartTime = std::chrono::steady_clock::now();
                std::cout << "NPC reached the goal. Waiting for 5 seconds..." << std::endl;
            }
        }
        else
        {
            updatePath(m_mapGraph);
            const sf::Vector2u nextTileToMove = getNextTileToMove();
            const sf::Vector2f targetPosition = Map::GetInstance().getPositionFromTile(nextTileToMove);
            moveTo(dt, targetPosition, currentPosition);
        }
    }
}

void NPC::loadTexture()
{
    m_texture->loadFromFile("Assets/NPC.png");
}

void NPC::harvestResource() 
{
    if (!m_taskAssigned) return;

    sf::Vector2u currentTile = Map::GetInstance().getTileFromPosition(m_sprite.getPosition());
    std::vector<sf::Vector2u> nearbyTiles = getAdjacentTilesforMine(currentTile);

    for (const auto& tile : nearbyTiles)
    {
        Resource* resource = ResourceManager::GetInstance().getResourceAt(tile);

        if (resource && !resource->isDestroyed()) {
            resource->destroy();
            std::vector<std::pair<int, int>> resourceTiles = resource->getTiles();

            for (const auto& resTile : resourceTiles) {
                Map::GetInstance().setObjectLayer(resTile.first, resTile.second, 0);
            }

            int quantity = 0;
            switch (resource->getType()) {
            case ResourceType::TREE:
                quantity = 15; 
                break;
            case ResourceType::STONE:
                quantity = 5; 
                break;
            case ResourceType::METAL:
                quantity = 3; 
                break;
            default:
                quantity = 0;
            }

            ResourceManager::GetInstance().createDroppedResource(resource->getType(), tile, quantity);

            m_isWaiting = true;
            m_goalTile = findRandomTile();
            m_taskAssigned = false;
            NpcManager::GetInstance().updateAllNpcsGraphs();
            break;
        }
    }
}

void NPC::transferResource()
{
    std::vector<Resource>& resources = ResourceManager::GetInstance().m_newResources;
    for (auto& resource : resources)
    {
        if (arePositionsApproximatelyEqual(resource.getPosition2f(), m_goalNextTile))
        {
            resource.setVisible(true);
        }
    }
    std::cout << "Complete transfer" << std::endl;
    m_isWaiting = true;
    m_goalTile = findRandomTile();
    m_taskAssigned = false;
}

bool NPC::arePositionsApproximatelyEqual(const sf::Vector2f& pos1, const sf::Vector2u& pos2, float tolerance) 
{
    return std::abs(pos1.x - pos2.x) < tolerance && std::abs(pos1.y - pos2.y) < tolerance;
}

std::vector<sf::Vector2u> NPC::getTreeTiles(const sf::Vector2u& startTile) const
{
    std::vector<sf::Vector2u> treeTiles;

    for (int dy = 0; dy < 2; ++dy)
    {
        for (int dx = 0; dx < 2; ++dx)
        {
            sf::Vector2u tile = { startTile.x + dx, startTile.y + dy };
            if (Map::GetInstance().isTileInBounds(tile))
            {
                if (Map::GetInstance().getObjectLayer(tile.x, tile.y) >= 4 && Map::GetInstance().getObjectLayer(tile.x, tile.y) <= 7)
                {
                    treeTiles.push_back(tile);
                }
            }
        }
    }

    return treeTiles;
}

void NPC::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);

    drawPath(window);
}

void NPC::drawPath(sf::RenderWindow& window) const
{
    if (m_path.empty()) return;

    sf::VertexArray lines(sf::LinesStrip, m_path.size());

    for (std::size_t i = 0; i < m_path.size(); ++i)
    {
        sf::Vector2f tilePosition = Map::GetInstance().getPositionFromTile(m_path[i]);
        lines[i].position = tilePosition;
        lines[i].color = sf::Color::Red;
    }

    window.draw(lines);
}

void NPC::setGraph(const Graph& graph) 
{
    m_mapGraph = graph;
}


Graph NPC::buildGraph()
{
    const unsigned mapSize = Map::MAP_SIZE;
    Graph graph(mapSize * mapSize);

    for (unsigned y = 0; y < mapSize; ++y)
    {
        for (unsigned x = 0; x < mapSize; ++x)
        {
            sf::Vector2u tilePosition(x, y);

            if (!Map::GetInstance().isTileBlocked(tilePosition))
            {
                unsigned vertex = convertMapTileToVertix(tilePosition);

                std::vector<sf::Vector2i> directions = {
                    {1, 0}, {0, 1}, {-1, 0}, {0, -1}
                    /*{1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1} */
                };

                for (const auto& dir : directions)
                {
                    sf::Vector2u neighbor(x + dir.x, y + dir.y);
                    if (neighbor.x < mapSize && neighbor.y < mapSize && !Map::GetInstance().isTileBlocked(neighbor))
                    {
                        graph.addEdge(vertex, convertMapTileToVertix(neighbor));
                    }
                }
            }
        }
    }

    return graph;
}

void NPC::updatePath(Graph& graph)
{
    const sf::Vector2u referenceTile = Map::GetInstance().getTileFromPosition(m_sprite.getPosition());
    const sf::Vector2u targetTile = m_goalTile;

    if (Map::GetInstance().isTileBlocked(targetTile))
    {
        m_goalTile = findRandomTile(); 
        return;
    }

    const unsigned startVertex = convertMapTileToVertix(referenceTile);
    const unsigned destinationVertex = convertMapTileToVertix(targetTile);

    std::vector<unsigned> path = graph.bfs(startVertex, destinationVertex);

    m_path.clear();
    for (unsigned vertex : path)
    {
        m_path.push_back(convertVertixToMapTile(vertex));
    }
}

sf::Vector2u NPC::getNextTileToMove()
{
    if (m_path.empty())
    {
        return Map::GetInstance().getTileFromPosition(m_sprite.getPosition());
    }

    if (m_path.size() > 1)
    {
        return m_path[1]; 
    }

    return m_path[0]; 
}

sf::Vector2u NPC::convertVertixToMapTile(unsigned vertex) const
{
    unsigned width = Map::GetInstance().getAllTiles()[0].size();
    return { vertex % width, vertex / width };
}

unsigned NPC::convertMapTileToVertix(sf::Vector2u mapTile) const
{
    unsigned width = Map::GetInstance().getAllTiles()[0].size();
    return mapTile.y * width + mapTile.x;
}

sf::Vector2u NPC::findRandomTile() const
{
    while (true)
    {
        sf::Vector2u randomTile(
            static_cast<unsigned>(rand() % Map::MAP_SIZE),
            static_cast<unsigned>(rand() % Map::MAP_SIZE)
        );

        if (!Map::GetInstance().isTileBlocked(randomTile))
        {
            return randomTile;
        }
    }
}

void NPC::moveTo(float dt, const sf::Vector2f& targetPosition, const sf::Vector2f& currentPosition)
{
    const float DeltaSpeed = dt * 400.0f;
    const float ArrivalThreshold = 1.0f;

    const sf::Vector2f Direction = targetPosition - currentPosition;

    if (MathHelper::GetLength(Direction) > ArrivalThreshold)
    {
        const sf::Vector2f NormalizedDirection = MathHelper::Normalize(Direction);

        m_sprite.move(NormalizedDirection * DeltaSpeed);
    }
    else
    {
        m_sprite.setPosition(targetPosition);
    }
}

void NPC::assignTaskForHarvest(const sf::Vector2u& resourceTile)
{
    if (m_taskAssigned)
    {
        std::cerr << "Task already assigned to NPC: " << m_name << std::endl;
        return;
    }

    std::vector<sf::Vector2u> adjacentTiles = getAdjacentTilesforWolking(resourceTile);

    if (!adjacentTiles.empty())
    {
        m_goalTile = adjacentTiles.front();
        std::cout << "add Harvest " << m_name << " " << m_goalTile.x << " " << m_goalTile.y << std::endl;
        m_isWaiting = false;
        m_taskAssigned = true; 
        m_currentWorkType = WorkType::HARVEST;
    }
    else
    {
        std::cerr << "No valid adjacent tiles found for resource task." << std::endl;
    }
}


void NPC::assignTaskForTransfer(const sf::Vector2u& fromTiles, const sf::Vector2u& ToTiles)
{
    if (m_taskAssigned)
    {
        std::cerr << "Task already assigned to NPC: " << m_name << std::endl;
        return;
    }

    m_goalTile = fromTiles;
    m_goalNextTile = ToTiles;
    std::cout << "add Transfe " << m_name << " " << m_goalTile.x << " " << m_goalTile.y << std::endl;
    m_isWaiting = false;
    m_taskAssigned = true;
    m_currentWorkType = WorkType::RESOURCE_TRANSFER;
}

bool NPC::isFree() const
{
    return !m_isWaiting && !m_taskAssigned && m_goalTile == Map::GetInstance().getTileFromPosition(m_sprite.getPosition());
}


sf::Vector2f NPC::getPosition() const
{
    return m_sprite.getPosition();
}

std::vector<sf::Vector2u> NPC::getAdjacentTilesforWolking(const sf::Vector2u& tile) const
{
    std::vector<sf::Vector2u> adjacentTiles;

    std::vector<sf::Vector2i> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
        /*{1, 0}, {0, 1}, {-1, 0}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}*/
    };

    for (const auto& dir : directions)
    {
        sf::Vector2u adjacentTile = tile;
        adjacentTile.x = static_cast<unsigned>(static_cast<int>(tile.x) + dir.x);
        adjacentTile.y = static_cast<unsigned>(static_cast<int>(tile.y) + dir.y);

        if (Map::GetInstance().isTileInBounds(adjacentTile) && !Map::GetInstance().isTileBlocked(adjacentTile))
        {
            adjacentTiles.push_back(adjacentTile);
        }
    }

    return adjacentTiles;
}


std::vector<sf::Vector2u> NPC::getAdjacentTilesforMine(const sf::Vector2u& tile) const
{
    std::vector<sf::Vector2u> adjacentTiles;

    std::vector<sf::Vector2i> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1} // Right, Down, Left, Up
    };

    for (const auto& dir : directions)
    {
        sf::Vector2u adjacentTile = tile;
        adjacentTile.x = static_cast<unsigned>(static_cast<int>(tile.x) + dir.x);
        adjacentTile.y = static_cast<unsigned>(static_cast<int>(tile.y) + dir.y);

        if (Map::GetInstance().isTileInBounds(adjacentTile) && Map::GetInstance().isTileBlocked(adjacentTile))
        {
            adjacentTiles.push_back(adjacentTile);
        }
    }

    return adjacentTiles;
}
