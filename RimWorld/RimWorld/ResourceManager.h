#pragma once
#include <vector>
#include "Resource.h"
#include "Map.h"

class ResourceManager
{
public:
    static ResourceManager& GetInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(); 

    void addResources(Map::TilesMapType map);
    Resource* getResourceAt(const sf::Vector2u& position);
    void draw(sf::RenderWindow& window);
    void createDroppedResource(ResourceType type, const sf::Vector2u& position, int quantity);
    std::vector<Resource> m_newResources;

private:
    std::vector<Resource> m_resources;
    Map::TilesMapType m_map; 
};
