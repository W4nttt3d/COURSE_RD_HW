#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "NPC.h" 
#include "MathHelper.h" 
#include "Resource.h"

enum class TaskType
{
    HARVEST,
    RESOURCE_TRANSFER
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

    NpcManager(const NpcManager&) = delete;
    NpcManager& operator=(const NpcManager&) = delete;
    void updateAllNpcsGraphs();

private:
    NpcManager();

    void assignQueuedTasks();
    sf::Vector2u findTileForTransfer(ResourceType type, const sf::Vector2u& fromTile);

    std::vector<NPC> m_npcs;
    std::queue<std::pair<TaskType, HarvestTask>> m_harvestTaskQueue;
    std::queue<std::pair<TaskType, TransferTask>> m_resourceTransferTaskQueue;
};
