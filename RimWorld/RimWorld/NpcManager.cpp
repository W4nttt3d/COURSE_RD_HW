#include "NpcManager.h"
#include "Graph.h"

NpcManager::NpcManager() {
    std::vector<std::string> npcNames = { "Alice", "Bob", "Charlie", "Diana" };

    for (int i = 0; i < 4; ++i) {
        m_npcs.emplace_back(npcNames[i]);
    }

    m_tileStatuses.resize(Map::GetInstance().MAP_SIZE, std::vector<TileStatus>(Map::GetInstance().MAP_SIZE));
}

void NpcManager::update(float dt) {
    for (auto& npc : m_npcs) {
        npc.update(dt);
    }

    assignQueuedTasks();
}

void NpcManager::draw(sf::RenderWindow& window) {
    for (auto& npc : m_npcs) {
        npc.draw(window);
    }
}

void NpcManager::updateAllNpcsGraphs() {
    for (auto& npc : m_npcs) {
        npc.setGraph(npc.buildGraph());
    }
}

void NpcManager::assignHarvestTask(const sf::Vector2u& tile) {
    if (m_tileStatuses[tile.y][tile.x].isBlocked) {
        m_harvestTaskQueue.push({ TaskType::HARVEST, {tile} });
        return;
    }

    NPC* closestNPC = findClosestFreeNPC(tile);
    if (closestNPC) {
        closestNPC->assignTaskForHarvest(tile);
        m_tileStatuses[tile.y][tile.x].block(TileTypeStatus::HARVEST);
    }
    else {
        m_harvestTaskQueue.push({ TaskType::HARVEST, {tile} });
    }
}

void NpcManager::assignResourceTransferTask(const sf::Vector2u& fromTile, ResourceType type) {
    NPC* closestNPC = findClosestFreeNPC(fromTile);
    sf::Vector2u toTile = findTileForTransfer(type, fromTile);

    if (closestNPC && toTile != sf::Vector2u(-1, -1)) {
        closestNPC->assignTaskForTransfer(fromTile, toTile);
        m_tileStatuses[toTile.y][toTile.x].block(TileTypeStatus::RESOURCE_TRANSFER);
    }
    else {
        TransferTask transferTask{ fromTile, toTile, type };
        m_resourceTransferTaskQueue.push({ TaskType::RESOURCE_TRANSFER, transferTask });
    }
}

void NpcManager::assignBuildTask(const sf::Vector2u& targetTile, ResourceType type, int number) {
    BuildTask buildTask{ findTileResource(type, number), targetTile, type, number };

    NPC* closestNPC = findClosestFreeNPC(targetTile);
    if (closestNPC && buildTask.fromTile != sf::Vector2u(-1, -1)) {
        closestNPC->assignTaskForBuild(buildTask.fromTile, buildTask.toTile, buildTask.requiredAmount);
    }
    else {
        m_buildTaskQueue.push({ TaskType::BUILD, buildTask });
    }
}

void NpcManager::assignQueuedTasks() {
    assignQueuedHarvestTasks();
    assignQueuedResourceTransferTasks();
    assignQueuedBuildTasks();
}

void NpcManager::assignQueuedHarvestTasks() {
    while (!m_harvestTaskQueue.empty()) {
        auto taskPair = m_harvestTaskQueue.front();
        m_harvestTaskQueue.pop();

        sf::Vector2u tile = taskPair.second.tile;
        NPC* closestNPC = findClosestFreeNPC(tile);

        if (closestNPC && !m_tileStatuses[tile.y][tile.x].isBlocked) {
            closestNPC->assignTaskForHarvest(tile);
            m_tileStatuses[tile.y][tile.x].block(TileTypeStatus::HARVEST);
        }
        else {
            m_harvestTaskQueue.push(taskPair);
            break;
        }
    }
}

void NpcManager::assignQueuedResourceTransferTasks() {
    while (!m_resourceTransferTaskQueue.empty()) {
        auto taskPair = m_resourceTransferTaskQueue.front();
        m_resourceTransferTaskQueue.pop();

        sf::Vector2u fromTile = taskPair.second.fromTile;
        ResourceType type = taskPair.second.type;
        sf::Vector2u toTile = findTileForTransfer(type, fromTile);

        NPC* closestNPC = findClosestFreeNPC(fromTile);

        if (closestNPC && toTile != sf::Vector2u(-1, -1)) {
            closestNPC->assignTaskForTransfer(fromTile, toTile);
            m_tileStatuses[toTile.y][toTile.x].block(TileTypeStatus::RESOURCE_TRANSFER);
        }
        else {
            taskPair.second.toTile = toTile;
            m_resourceTransferTaskQueue.push(taskPair);
            break;
        }
    }
}

void NpcManager::assignQueuedBuildTasks() {
    while (!m_buildTaskQueue.empty()) {
        auto taskPair = m_buildTaskQueue.front();
        m_buildTaskQueue.pop();

        ResourceType type = taskPair.second.type;
        sf::Vector2u fromTile = findTileResource(type, taskPair.second.requiredAmount);
        sf::Vector2u toTile = taskPair.second.toTile;

        NPC* closestNPC = findClosestFreeNPC(toTile);

        if (closestNPC && fromTile != sf::Vector2u(-1, -1)) {
            closestNPC->assignTaskForBuild(fromTile, toTile, taskPair.second.requiredAmount);
        }
        else {
            m_buildTaskQueue.push(taskPair);
            break;
        }
    }
}

NPC* NpcManager::findClosestFreeNPC(const sf::Vector2u& tile) {
    NPC* closestNPC = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (auto& npc : m_npcs) {
        if (npc.isFree()) {
            float distance = MathHelper::GetLength(npc.getPosition() - Map::GetInstance().getPositionFromTile(tile));
            if (distance < minDistance) {
                minDistance = distance;
                closestNPC = &npc;
            }
        }
    }

    return closestNPC;
}

sf::Vector2u NpcManager::findTileResource(ResourceType type, int number) {
    std::vector<Resource>& resources = ResourceManager::GetInstance().m_newResources;

    for (unsigned y = 0; y < Map::GetInstance().MAP_SIZE; y++) {
        for (unsigned x = 0; x < Map::GetInstance().MAP_SIZE; x++) {
            sf::Vector2u currentTile(x, y);

            int tileValue = Map::GetInstance().getObjectLayer(x, y);
            if (tileValue == 12) {
                for (const auto& resource : resources) {
                    if (currentTile == resource.getPosition2u() &&
                        resource.getType() == type && resource.getQuantity() >= number) {
                        return currentTile;
                    }
                }
            }
        }
    }
    return sf::Vector2u(-1, -1);
}

sf::Vector2u NpcManager::findTileForTransfer(ResourceType type, const sf::Vector2u& fromTile) {
    std::vector<Resource>& resources = ResourceManager::GetInstance().m_newResources;

    for (unsigned y = 0; y < Map::GetInstance().MAP_SIZE; y++) {
        for (unsigned x = 0; x < Map::GetInstance().MAP_SIZE; x++) {
            sf::Vector2u currentTile(x, y);

            if (currentTile == fromTile) {
                continue;
            }

            int tileValue = Map::GetInstance().getObjectLayer(x, y);
            if (tileValue == 12) {
                bool hasMatchingResource = false;
                bool hasOtherResource = false;

                for (const auto& resource : resources) {
                    if (currentTile == resource.getPosition2u()) {
                        if (resource.getType() == type) {
                            hasMatchingResource = true;
                        }
                        else {
                            hasOtherResource = true;
                        }
                        break;
                    }
                }

                if (hasMatchingResource || (!hasOtherResource && !m_tileStatuses[currentTile.y][currentTile.x].isBlocked)) {
                    return currentTile;
                }
            }
        }
    }
    return sf::Vector2u(-1, -1);
}

void NpcManager::onTaskCompleted(const sf::Vector2u& tile) {
    m_tileStatuses[tile.y][tile.x].unblock();
}
