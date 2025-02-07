#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "NPC.h" 
#include "MathHelper.h" 
#include "Resource.h"
#include <set>
#include "TileStatus.h"

enum class TaskType
{
    HARVEST,
    RESOURCE_TRANSFER,
    BUILD
};

struct HarvestTask
{
    sf::Vector2u tile;
};

struct TransferTask
{
    sf::Vector2u fromTile;
    sf::Vector2u toTile;
    ResourceType type;  
};

struct BuildTask
{
    sf::Vector2u fromTile;
    sf::Vector2u toTile;
    ResourceType type; 
    int requiredAmount;           
};

class NpcManager {
public:
    static NpcManager& GetInstance()
    {
        static NpcManager instance;
        return instance;
    }

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void assignHarvestTask(const sf::Vector2u& tile);
    void assignResourceTransferTask(const sf::Vector2u& fromTile, ResourceType type);
    void assignBuildTask(const sf::Vector2u& targetTile, ResourceType type, int number);

    NpcManager(const NpcManager&) = delete;
    NpcManager& operator=(const NpcManager&) = delete;
    void updateAllNpcsGraphs();
    void onTaskCompleted(const sf::Vector2u& tile);

private:
    NpcManager();

    void assignQueuedTasks();
    void assignQueuedHarvestTasks();
    void assignQueuedResourceTransferTasks();
    void assignQueuedBuildTasks();
    NPC* findClosestFreeNPC(const sf::Vector2u& tile);
    sf::Vector2u findTileForTransfer(ResourceType type, const sf::Vector2u& fromTile);
    sf::Vector2u findTileResource(ResourceType type, int number);

    std::vector<NPC> m_npcs;
    std::queue<std::pair<TaskType, HarvestTask>> m_harvestTaskQueue;
    std::queue<std::pair<TaskType, TransferTask>> m_resourceTransferTaskQueue;
    std::queue<std::pair<TaskType, BuildTask>> m_buildTaskQueue;
    std::set<sf::Vector2u> occupiedTiles;
    std::vector<std::vector<TileStatus>> m_tileStatuses;
};
