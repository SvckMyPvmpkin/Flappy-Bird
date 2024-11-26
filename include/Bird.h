#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObject.h"

class Bird : public IGameObject {
public:
    virtual ~Bird() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void jump() = 0;
    virtual void reset() = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::FloatRect getRect() const = 0;
};

class Player : public Bird {
private:
    sf::Sprite sprite;
    sf::FloatRect rect;
    float dx, dy;
    float currentFrame;

    static constexpr float gravity = 0.0005f;
    static constexpr float jumpForce = -0.2f;

public:
    bool onGround;

    explicit Player(const sf::Texture& texture) 
        : dx(0), dy(0), currentFrame(0), onGround(false) {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 40, 33));
        rect = {125, 100, 40, 33};
    }

    void update(float deltaTime) override {
        rect.left += dx * deltaTime;

        if (!onGround) {
            dy += gravity * deltaTime;
        }

        rect.top += dy * deltaTime;

        if (rect.top > 480) {
            rect.top = 480;
            dy = 0;
            onGround = true;
        }

        currentFrame += 0.005f * deltaTime;
        if (currentFrame > 3) {
            currentFrame -= 3;
        }
        sprite.setTextureRect(sf::IntRect(40 * static_cast<int>(currentFrame), 0, 40, 33));
        sprite.setPosition(rect.left, rect.top);
    }

    void draw(sf::RenderWindow& window) const override {
        window.draw(sprite);
    }

    void jump() override {
        dy = jumpForce;
        onGround = false;
    }

    void reset() override {
        rect.left = 125;
        rect.top = 100;
        dx = 0;
        dy = 0;
        onGround = false;
    }

    sf::FloatRect getBounds() const override {
        return sprite.getGlobalBounds();
    }

    sf::FloatRect getRect() const override {
        return rect;
    }
};
