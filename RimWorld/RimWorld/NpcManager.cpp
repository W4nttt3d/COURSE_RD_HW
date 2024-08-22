#include "NpcManager.h"
#include "Graph.h"

NpcManager::NpcManager() {
    std::vector<std::string> npcNames = { "Alice", "Bob", "Charlie", "Diana" };

    for (int i = 0; i < 4; ++i) {
        m_npcs.emplace_back(npcNames[i]);
    }
}

void NpcManager::update(float dt)
{
    for (auto& npc : m_npcs)
    {
        npc.update(dt);
    }

    assignQueuedTasks();
}

void NpcManager::draw(sf::RenderWindow& window)
{
    for (auto& npc : m_npcs)
    {
        npc.draw(window);
    }
}

void NpcManager::updateAllNpcsGraphs() 
{
    for (auto& npc : m_npcs) 
    {
        npc.setGraph(npc.buildGraph());
    }
}


void NpcManager::assignHarvestTask(const sf::Vector2u& tile)
{
    NPC* closestNPC = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (auto& npc : m_npcs)
    {
        if (npc.isFree())
        {
            float distance = MathHelper::GetLength(npc.getPosition() - Map::GetInstance().getPositionFromTile(tile));
            if (distance < minDistance)
            {
                minDistance = distance;
                closestNPC = &npc;
            }
        }
    }

    HarvestTask harvestTask;
    harvestTask.tile = tile;

    if (closestNPC)
    {
        closestNPC->assignTaskForHarvest(tile);
    }
    else
    {
        m_harvestTaskQueue.push({ TaskType::HARVEST, harvestTask });
    }
}

void NpcManager::assignResourceTransferTask(const sf::Vector2u& fromTile, ResourceType type)
{
    NPC* closestNPC = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (auto& npc : m_npcs)
    {
        if (npc.isFree())
        {
            float distance = MathHelper::GetLength(npc.getPosition() - Map::GetInstance().getPositionFromTile(fromTile));
            if (distance < minDistance)
            {
                minDistance = distance;
                closestNPC = &npc;
            }
        }
    }

    TransferTask transferTask;
    transferTask.fromTile = fromTile;
    transferTask.toTile = findTileForTransfer(type, fromTile);
    transferTask.type = type; 

    if (closestNPC && transferTask.toTile != sf::Vector2u(-1, -1))
    {
        closestNPC->assignTaskForTransfer(fromTile, transferTask.toTile);
    }
    else
    {
        m_resourceTransferTaskQueue.push({ TaskType::RESOURCE_TRANSFER, transferTask });
    }
}

void NpcManager::assignQueuedTasks()
{
    if (m_harvestTaskQueue.empty())
    {
        if (!m_resourceTransferTaskQueue.empty())
        {
            auto taskPair = m_resourceTransferTaskQueue.front();
            m_resourceTransferTaskQueue.pop();

            sf::Vector2u fromTile = taskPair.second.fromTile;
            sf::Vector2u toTile = taskPair.second.toTile;
            ResourceType type = taskPair.second.type;  

            if (toTile == sf::Vector2u(-1, -1))
            {
                toTile = findTileForTransfer(type, fromTile);
            }

            NPC* closestNPC = nullptr;
            float minDistance = std::numeric_limits<float>::max();

            for (auto& npc : m_npcs)
            {
                if (npc.isFree())
                {
                    float distance = MathHelper::GetLength(npc.getPosition() - Map::GetInstance().getPositionFromTile(fromTile));
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestNPC = &npc;
                    }
                }
            }

            if (closestNPC && toTile != sf::Vector2u(-1, -1))
            {
                closestNPC->assignTaskForTransfer(fromTile, toTile);
            }
            else
            {
                taskPair.second.toTile = toTile;
                m_resourceTransferTaskQueue.push(taskPair);
            }
        }
    }
    else
    {
        while (!m_harvestTaskQueue.empty())
        {
            auto taskPair = m_harvestTaskQueue.front();
            m_harvestTaskQueue.pop();

            sf::Vector2u tile = taskPair.second.tile;

            NPC* closestNPC = nullptr;
            float minDistance = std::numeric_limits<float>::max();

            for (auto& npc : m_npcs)
            {
                if (npc.isFree())
                {
                    float distance = MathHelper::GetLength(npc.getPosition() - Map::GetInstance().getPositionFromTile(tile));
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestNPC = &npc;
                    }
                }
            }

            if (closestNPC)
            {
                HarvestTask harvestTask;
                harvestTask.tile = tile;
                closestNPC->assignTaskForHarvest(harvestTask.tile);
            }
            else
            {
                m_harvestTaskQueue.push({ TaskType::HARVEST, taskPair.second });
                break;
            }
        }
    }
}

sf::Vector2u NpcManager::findTileForTransfer(ResourceType type, const sf::Vector2u& fromTile)
{
    std::vector<Resource>& resources = ResourceManager::GetInstance().m_newResources;

    for (unsigned y = 0; y < Map::GetInstance().MAP_SIZE; y++)
    {
        for (unsigned x = 0; x < Map::GetInstance().MAP_SIZE; x++)
        {
            sf::Vector2u currentTile(x, y);

            if (currentTile == fromTile)
            {
                continue;
            }

            bool hasResource = false;
            for (const auto& resource : resources)
            {
                const auto& tiles = resource.getTiles();
                if (std::find(tiles.begin(), tiles.end(), std::make_pair(x, y)) != tiles.end())
                {
                    if (resource.getType() != type)
                    {
                        hasResource = true;
                    }
                    break;
                }
            }

            if (!hasResource)
            {
                int tileValue = Map::GetInstance().getObjectLayer(x, y);
                if (tileValue == 12)
                {
                    return currentTile;
                }
            }
        }
    }
    return sf::Vector2u(-1, -1);
}
