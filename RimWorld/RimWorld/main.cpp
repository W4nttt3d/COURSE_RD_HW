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
                std::cout << "Building mode" << std::endl;
                isPlacingMode = !isPlacingMode;
                building.setPlacing(isPlacingMode);
            }
            else if (event.key.code == sf::Keyboard::Key::Z)
            {
                std::cout << "Zoning mode" << std::endl;
                isZoningMod = !isZoningMod;
                building.setZoning(isZoningMod);
            }
            else if (event.key.code == sf::Keyboard::Key::O)
            {
                std::cout << "Orders mode" << std::endl;
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

class Button {
public:
    Button(const std::string& text, const sf::Vector2f& position, const sf::Font& font, const sf::Texture& buttonTexture) 
    {
        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(position.x + 10.f, position.y + 10.f);
        buttonShape.setSize(sf::Vector2f(200.f, 50.f)); 
        buttonShape.setTexture(&buttonTexture); 
        buttonShape.setPosition(position); 
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    bool isMouseOver(sf::Vector2i mousePosition) {
        return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
    }

    void setFillColor(sf::Color color) {
        buttonShape.setFillColor(color);
    }

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};

void showMainMenu(sf::RenderWindow& window, sf::Font& font, const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture) {
    Button newColonyButton("New Colony", { static_cast<float>(window.getSize().x) - 250.f, 200.f }, font, buttonTexture);
    Button exitButton("Exit", { static_cast<float>(window.getSize().x) - 250.f, 300.f }, font, buttonTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newColonyButton.isMouseOver(sf::Mouse::getPosition(window))) 
                    {
                        return;
                    }
                    else if (exitButton.isMouseOver(sf::Mouse::getPosition(window))) 
                    {
                        window.close(); 
                    }
                }
            }
        }

        window.clear();
        window.draw(sf::Sprite(backgroundTexture)); 
        newColonyButton.draw(window);
        exitButton.draw(window);
        window.display();
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow& window = WindowHelper::Instance().GetRenderWindow();
    sf::Font font;
    if (!font.loadFromFile("Assets/FixelDisplay-Bold.ttf")) 
    { 
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Assets/BGPlanet.png")) 
    { 
        std::cerr << "Failed to load background image!" << std::endl;
        return -1;
    }

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("Assets/Block.png")) 
    { 
        std::cerr << "Failed to load button texture!" << std::endl;
        return -1;
    }

    showMainMenu(window, font, backgroundTexture, buttonTexture);

    CameraController cameraController(window.getSize().x, window.getSize().y);
    NpcManager& npcManager = NpcManager::GetInstance();
    ResourceManager resourceManager;

    Tool building;

    sf::Clock clock;

    while (window.isOpen()) {
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
