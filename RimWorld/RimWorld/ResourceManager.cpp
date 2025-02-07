#include "ResourceManager.h"
#include "Resource.h"
#include <iostream>
#include "NpcManager.h"

ResourceManager::ResourceManager()
{
    m_font.loadFromFile("Assets/FixelDisplay-Bold.ttf");
}

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
                    resources.push_back({ResourceType::TREE, {{x, y}, {x + 1, y}, {x, y + 1}, {x + 1, y + 1}}, 15 });

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
        droppedResource.setFont(&m_font);
        m_newResources.push_back(droppedResource);
        std::cout << quantity << std::endl;
        NpcManager::GetInstance().assignResourceTransferTask(droppedResource.getPosition2u(), droppedResource.getType());
    }
}

void ResourceManager::removeResource(const sf::Vector2u& position)
{
    // Пошук ресурсу за позицією
    auto it = std::remove_if(m_resources.begin(), m_resources.end(),
        [&position](const Resource& resource)
        {
            const auto& tiles = resource.getTiles();
            return std::find(tiles.begin(), tiles.end(), std::make_pair(position.x, position.y)) != tiles.end();
        });

    // Видаляємо ресурс, якщо знайдений
    if (it != m_resources.end())
    {
        m_resources.erase(it, m_resources.end());
    }
}

