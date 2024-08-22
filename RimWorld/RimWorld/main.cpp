#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <thread>

#include "Component.h"
#include "Map.h"
#include "Tool.h"
#include "NpcManager.h"
#include "ResourceManager.h"

#include "WindowHelper.h"

bool isPlacingMode = false;
bool isZoningMod = false;
bool isOrdersMod = false;
Tool building;

void handleSystemEvents(sf::RenderWindow& window, CameraController& cameraControl, Tool& building, NpcManager& npcManager)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::Key::B)
            {
                std::cout << "Building mod" << std::endl;
                isPlacingMode = !isPlacingMode;
                building.setPlacing(isPlacingMode);
            }
            else if (event.key.code == sf::Keyboard::Key::Z)
            {
                std::cout << "Zoning mod" << std::endl;
                isZoningMod = !isZoningMod;
                building.setZoning(isZoningMod);
            }
            else if (event.key.code == sf::Keyboard::Key::O)
            {
                std::cout << "Orders mod" << std::endl;
                isOrdersMod = !isOrdersMod;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (isOrdersMod)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    building.handleMouseClick(event.mouseButton.x, event.mouseButton.y, window, npcManager);
                }
            }
            break;
        case sf::Event::MouseWheelScrolled:
            cameraControl.handleEvent(event);
            break;
        default:
            break;
        }
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow& window = WindowHelper::Instance().GetRenderWindow();
    CameraController cameraController(window.getSize().x, window.getSize().y);
    NpcManager& npcManager = NpcManager::GetInstance();
    ResourceManager resourceManager;

    sf::Clock clock;

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();

        handleSystemEvents(window, cameraController, building, npcManager); 
        cameraController.update(deltaTime);

        sf::View view = window.getView();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        building.update(mousePosition, window, view);
        npcManager.update(deltaTime);

        window.clear();
        Map::GetInstance().draw(&window);
        building.draw(window);
        npcManager.draw(window);
        resourceManager.GetInstance().draw(window);
        cameraController.apply(window);
        window.display();
    }
}
