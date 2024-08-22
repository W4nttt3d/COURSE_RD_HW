#include "Component.h"

CameraController::CameraController(float windowWidth, float windowHeight)
    : m_view(sf::FloatRect(0, 0, windowWidth, windowHeight)),
    m_moveSpeed(500.0f), 
    m_zoomFactor(1.08f),  
    m_zoomInRequested(false),
    m_zoomOutRequested(false)
{

}

void CameraController::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_view.move(0, -m_moveSpeed * deltaTime); // Up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_view.move(0, m_moveSpeed * deltaTime); // Down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_view.move(-m_moveSpeed * deltaTime, 0); // Left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_view.move(m_moveSpeed * deltaTime, 0); // Right
    }

    if (m_zoomInRequested) {
        m_view.zoom(1.0f / m_zoomFactor); // +
        m_zoomInRequested = false;
    }
    if (m_zoomOutRequested) {
        m_view.zoom(m_zoomFactor); // -
        m_zoomOutRequested = false;
    }
}

void CameraController::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            m_zoomInRequested = true;
        }
        else if (event.mouseWheelScroll.delta < 0)
        {
            m_zoomOutRequested = true;
        }
    }
}

void CameraController::apply(sf::RenderWindow& window)
{
    window.setView(m_view);
}