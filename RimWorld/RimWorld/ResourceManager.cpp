#include "ResourceManager.h"
#include "Resource.h"
#include <iostream>
#include "NpcManager.h"

ResourceManager::ResourceManager(){}

void ResourceManager::addResources(Map::TilesMapType map)
{
    m_map = map;
    std::vector<Resource> resources;

    for (int y = 0; y < map.size(); ++y)
    {
        for (int x = 0; x < map[y].size(); ++x)
        {
            if (map[y][x] == static_cast<int>(ResourceType::TREE))
            {
                if (x < map[y].size() - 1 && y < map.size() - 1 &&
                    map[y][x + 1] == 6 &&
                    map[y + 1][x] == 5 &&
                    map[y + 1][x + 1] == 4)
                {
                    resources.push_back({
                        ResourceType::TREE,
                        {{x, y}, {x + 1, y}, {x, y + 1}, {x + 1, y + 1}},
                        15 
                        });

                    map[y][x] = 0;
                    map[y][x + 1] = 0;
                    map[y + 1][x] = 0;
                    map[y + 1][x + 1] = 0;
                }
            }
        }
    }

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == static_cast<int>(ResourceType::STONE)) {
                resources.push_back({ResourceType::STONE,{{x, y}},5 });
                map[y][x] = 0;
            }
            else if (map[y][x] == static_cast<int>(ResourceType::METAL)) {
                resources.push_back({ResourceType::METAL,{{x, y}},3 });
                map[y][x] = 0;
            }
        }
    }

    m_resources.insert(m_resources.end(), resources.begin(), resources.end());
}

Resource* ResourceManager::getResourceAt(const sf::Vector2u& position)
{
    for (auto& resource : m_resources)
    {
        const auto& tiles = resource.getTiles();
        if (std::find(tiles.begin(), tiles.end(), std::make_pair(position.x, position.y)) != tiles.end())
        {
            return &resource;
        }
    }
    return nullptr;
}

void ResourceManager::draw(sf::RenderWindow& window)
{
    for (const auto& resource : m_newResources)
    {
        resource.draw(window);
    }
}

void ResourceManager::createDroppedResource(ResourceType type, const sf::Vector2u& position, int quantity)
{
    if (position.x >= 0 && position.y >= 0 && position.x < m_map[0].size() && position.y < m_map.size())
    {
        Resource droppedResource(type, { {static_cast<int>(position.x), static_cast<int>(position.y)} }, quantity);
        m_newResources.push_back(droppedResource);
        std::cout << quantity << std::endl;
        NpcManager::GetInstance().assignResourceTransferTask(droppedResource.getPosition2u(), droppedResource.getType());
    }
}