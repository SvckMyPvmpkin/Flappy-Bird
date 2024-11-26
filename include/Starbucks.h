#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include "IGameObject.h"

class Pipe : public IGameObject {
private:
    std::array<sf::Sprite, 2> sprites;
    sf::FloatRect rect;
    int yOffset;
    float speed;
    bool active;
    bool scored;  
    static constexpr int pipeWidth = 60;
    static constexpr int pipeHeight = 415;
    static constexpr int gapHeight = 150;

public:
    explicit Pipe(const sf::Texture& texture, float initialSpeed)
        : speed(initialSpeed), active(false), scored(false) {
        for (auto& sprite : sprites) {
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, pipeWidth, pipeHeight));
        }
        sprites[1].setTextureRect(sf::IntRect(0, pipeHeight, pipeWidth, -pipeHeight));
        reset();
    }

    void update(float deltaTime) override {
        if (active) {
            rect.left += speed * deltaTime;

            if (rect.left < -pipeWidth) {
                reset();
            }

            sprites[0].setPosition(rect.left, rect.top);
            sprites[1].setPosition(rect.left, rect.top - gapHeight - pipeHeight);
        }
    }

    void draw(sf::RenderWindow& window) const override {
        if (active) {
            window.draw(sprites[0]);
            window.draw(sprites[1]);
        }
    }

    void reset() override {
        yOffset = getRandomYOffset();
        rect.left = 288;
        rect.top = 300 + 50 * yOffset;
        active = true;
        scored = false;  
    }

    bool isActive() const {
        return active;
    }

    void setActive(bool state) {
        active = state;
    }

    bool hasScored() const {
        return scored;
    }

    void setScored(bool state) {
        scored = state;
    }

    std::array<sf::FloatRect, 2> getBounds() const {
        return {
            sprites[0].getGlobalBounds(),
            sprites[1].getGlobalBounds()
        };
    }

    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    float getSpeed() const {
        return speed;
    }

private:
    int getRandomYOffset() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_int_distribution<int> distribution(-2, 2);
        return distribution(generator);
    }
};
