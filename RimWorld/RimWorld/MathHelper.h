#pragma once
#include <SFML/Window.hpp>
#include <cmath> 

class MathHelper
{
public:
    inline static float GetLength(const sf::Vector2f& vec)
    {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    inline static sf::Vector2f Normalize(const sf::Vector2f& vec)
    {
        const float len = GetLength(vec);
        if (len != 0)
        {
            return vec / len;
        }
        return sf::Vector2f(0, 0);
    }
};
