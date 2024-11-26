#pragma once
#include <SFML/Graphics.hpp>

class IGameObject {
public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void reset() = 0;
    virtual ~IGameObject() = default;
};
