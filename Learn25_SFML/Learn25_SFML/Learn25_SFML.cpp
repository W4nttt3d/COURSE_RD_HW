#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Boundaries
{
public:
	Boundaries(const sf::RenderWindow& window, const sf::Sprite& gameObject)
	{
		update(window, gameObject);
	}

	void update(const sf::RenderWindow& window, const sf::Sprite& gameObject)
	{
		float width = window.getSize().x - 40;
		float height = window.getSize().y - 40;
		float halfWidth = gameObject.getGlobalBounds().width / 2.0f;
		float halfHeight = gameObject.getGlobalBounds().height / 2.0f;

		leftBoundary = halfWidth + 40;
		rightBoundary = width - halfWidth;
		topBoundary = halfHeight + 40;
		bottomBoundary = height - halfHeight;
	}

	bool isWithinBounds(const sf::Vector2f& position) const
	{
		return position.x >= leftBoundary && position.x <= rightBoundary && position.y >= topBoundary && position.y <= bottomBoundary;
	}

private:
	float leftBoundary;
	float rightBoundary;
	float topBoundary;
	float bottomBoundary;
};

void handleMovment(sf::Sprite& gameObject, const Boundaries& boundaries)
{
	float DeltaX = 0.0f;
	float DeltaY = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		DeltaY = -0.6f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		DeltaY = 0.6f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		DeltaX = -0.6f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		DeltaX = 0.6f;
	}

	const sf::Vector2f oldPosition = gameObject.getPosition();
	sf::Vector2f newPosition = sf::Vector2f( oldPosition.x + DeltaX, oldPosition.y + DeltaY );

	if (boundaries.isWithinBounds(newPosition))
	{
		gameObject.setPosition(newPosition);
	}
}

void handleRotation(sf::Sprite& gameObject)
{
	float rotationSpeed = 0.5f; 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		gameObject.rotate(-rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	{
		gameObject.rotate(rotationSpeed);
	}
}

void handleScale(sf::Sprite& gameObject)
{
	float scaleSpeed = 0.001f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		gameObject.scale(1.0f + scaleSpeed, 1.0f + scaleSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
	{
		gameObject.scale(1.0f - scaleSpeed, 1.0f - scaleSpeed);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Learn25");

	sf::Texture playerTexture;
	playerTexture.loadFromFile("persona.png");

	sf::Sprite player;
	player.setTexture(playerTexture);

	sf::Vector2f playerPosition = { window.getSize().x / 2.0f , window.getSize().y / 2.0f };
	player.setPosition(playerPosition);
	player.setOrigin(player.getGlobalBounds().getSize().x / 2, player.getGlobalBounds().getSize().y / 2);

	Boundaries boundaries(window, player);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				boundaries.update(window, player);
				break;
			}
		}

		handleMovment(player, boundaries);
		handleRotation(player);
		handleScale(player);
		boundaries.update(window, player);

		window.clear(sf::Color{ 0, 255, 0 });

		window.draw(player);

		window.display();
	}
}
