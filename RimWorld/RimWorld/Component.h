#pragma once
#include <SFML/Graphics.hpp>

class Component
{
public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow* window) {}

    virtual ~Component() {};
};

class CameraController : public Component
{
public:
    CameraController(float windowWidth, float windowHeight);

    void update(float deltaTime) override;
    void handleEvent(const sf::Event& event);
    void apply(sf::RenderWindow& window);

private:
    sf::View m_view;
    float m_moveSpeed;
    float m_zoomFactor;
    bool m_zoomInRequested;
    bool m_zoomOutRequested;
};
