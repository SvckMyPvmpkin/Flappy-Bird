#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "IGameObject.h"

class Score : public IGameObject {
private:
    static constexpr int MAX_DIGITS = 3;  // Максимум 3 цифры (0-999)
    static constexpr int DIGIT_WIDTH = 44;  // Ширина одной цифры в текстуре
    static constexpr int DIGIT_HEIGHT = 45; // Высота одной цифры в текстуре
    static constexpr float DIGIT_SPACING = 2.0f; // Расстояние между цифрами

    std::array<sf::Sprite, MAX_DIGITS> digits;
    int count;
    bool canIncrement;
    static constexpr float updateDelay = 200.0f;
    float updateTimer;
    sf::Texture const* texture;

public:
    explicit Score(const sf::Texture& tex) 
        : count(0), canIncrement(true), updateTimer(0), texture(&tex) {
        // Инициализируем все спрайты
        for (auto& digit : digits) {
            digit.setTexture(*texture);
            digit.setTextureRect(sf::IntRect(0, 0, DIGIT_WIDTH, DIGIT_HEIGHT));
        }
        updateDigitPositions();
    }

    void update(float deltaTime) override {
        if (!canIncrement) {
            updateTimer += deltaTime;
            if (updateTimer >= updateDelay) {
                canIncrement = true;
                updateTimer = 0;
            }
        }
    }

    void draw(sf::RenderWindow& window) const override {
        // Определяем, сколько цифр нужно отображать
        int numDigits = (count == 0) ? 1 : static_cast<int>(log10(count)) + 1;
        for (int i = 0; i < numDigits; ++i) {
            window.draw(digits[i]);
        }
    }

    void reset() override {
        count = 0;
        canIncrement = true;
        updateTimer = 0;
        updateTextureRects();
        updateDigitPositions();
    }

    void increment() {
        if (canIncrement && count < 999) {  // Ограничиваем счет до 999
            count++;
            canIncrement = false;
            updateTextureRects();
            updateDigitPositions();
        }
    }

    bool canAdd() const {
        return canIncrement;
    }

    int getCount() const {
        return count;
    }

private:
    void updateTextureRects() {
        int tempCount = count;
        int numDigits = (count == 0) ? 1 : static_cast<int>(log10(count)) + 1;

        // Обновляем текстурные прямоугольники для каждой цифры
        for (int i = 0; i < numDigits; ++i) {
            int digit = (i == 0 && tempCount == 0) ? 0 : tempCount % 10;
            digits[i].setTextureRect(sf::IntRect(digit * DIGIT_WIDTH, 0, DIGIT_WIDTH, DIGIT_HEIGHT));
            tempCount /= 10;
        }
    }

    void updateDigitPositions() {
        int numDigits = (count == 0) ? 1 : static_cast<int>(log10(count)) + 1;
        float totalWidth = numDigits * DIGIT_WIDTH + (numDigits - 1) * DIGIT_SPACING;
        float startX = 144.0f - totalWidth / 2.0f; // Центрируем относительно середины экрана (288/2)

        // Расставляем цифры справа налево
        for (int i = 0; i < numDigits; ++i) {
            float x = startX + (numDigits - 1 - i) * (DIGIT_WIDTH + DIGIT_SPACING);
            digits[i].setPosition(x, 50.0f);
        }
    }
};