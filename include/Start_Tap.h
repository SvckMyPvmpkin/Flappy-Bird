#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObject.h"

class StartTap : public IGameObject {
private:
    sf::Sprite sprite;
    bool visible;
    float timer;
    static constexpr float maxTime = 1000.0f;

public:
    explicit StartTap(const sf::Texture& texture) 
        : visible(true), timer(maxTime) {
        sprite.setTexture(texture);
        sprite.setPosition(120, 200);
    }

    void update(float deltaTime) override {
        timer -= deltaTime;

        if (timer <= 0) {
            visible = !visible;
            timer = maxTime;
        }
    }

    void draw(sf::RenderWindow& window) const override {
        if (visible) {
            window.draw(sprite);
        }
    }

    void reset() override {
        timer = maxTime;
        visible = true;
    }

    void setVisible(bool state) {
        visible = state;
    }

    bool isVisible() const {
        return visible;
    }
};