#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Bird.h"
#include "Start_Tap.h"
#include "Starbucks.h"
#include "Score.h"
#include "GameState.h"
#include "CollisionManager.h"

class Game {
private:
    sf::RenderWindow window;
    GameState gameState;
    sf::Clock clock;
    
    sf::Texture backTexture;
    sf::Sprite background;
    
    sf::Texture birdTexture;
    std::unique_ptr<Bird> bird;
    
    sf::Texture startTapTexture;
    std::unique_ptr<StartTap> startTap;
    
    sf::Texture pipeTexture;
    Pipe pipe;
    
    sf::Texture scoreTexture;
    Score score;
    
    sf::Texture gameOverTexture;
    sf::Sprite gameOverScreen;

public:
    Game() : 
        window(sf::VideoMode(288, 512), "Flappy-The-Intelligent-Bird"),
        gameState(GameState::Start),
        pipe(pipeTexture, -0.05f),
        score(scoreTexture)
    {
        loadResources();
        initializeObjects();
    }

    void run() {
        while (window.isOpen()) {
            float deltaTime = clock.restart().asMicroseconds() / 800.0f;
            processEvents();
            update(deltaTime);
            render();
        }
    }

private:
    void loadResources() {
        if (!backTexture.loadFromFile("Sprite-0001.png") ||
            !birdTexture.loadFromFile("Sprite-0002.png") ||
            !startTapTexture.loadFromFile("Sprite-0003.png") ||
            !pipeTexture.loadFromFile("Sprite-0004.png") ||
            !scoreTexture.loadFromFile("Sprite-0005.png") ||
            !gameOverTexture.loadFromFile("Sprite-0006.png")) {
            throw std::runtime_error("Failed to load textures");
        }
    }

    void initializeObjects() {
        background.setTexture(backTexture);
        bird = std::make_unique<Player>(birdTexture);
        startTap = std::make_unique<StartTap>(startTapTexture);
        gameOverScreen.setTexture(gameOverTexture);
        gameOverScreen.setPosition(30, 300);
        
        // Reinitialize objects with loaded textures
        pipe = Pipe(pipeTexture, -0.05f);
        score = Score(scoreTexture);
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (gameState == GameState::Playing) {
                    bird->jump();
                }
            }
        }
    }

    void handleMouseClick() {
        switch (gameState) {
            case GameState::Start:
                gameState = GameState::Playing;
                bird->reset();
                pipe.reset();
                startTap->setVisible(false);
                break;
            case GameState::Playing:
                bird->jump();
                break;
            case GameState::GameOver:
                gameState = GameState::Start;
                resetGame();
                break;
        }
    }

    void update(float deltaTime) {
        if (gameState == GameState::Playing) {
            bird->update(deltaTime);
            pipe.update(deltaTime);
            score.update(deltaTime);
            checkCollisions();
            updateScore();
        }
        
        if (gameState == GameState::Start) {
            startTap->update(deltaTime);
        }
    }

    void checkCollisions() {
        if (CollisionManager::checkCollisions(bird.get(), pipe) ||
            CollisionManager::checkWindowBounds(bird.get(), window.getSize().y)) {
            gameState = GameState::GameOver;
        }
    }

    void updateScore() {
        auto pipeBounds = pipe.getBounds();
        if (!pipe.hasScored() && pipeBounds[0].left + pipeBounds[0].width < bird->getRect().left) {
            score.increment();
            pipe.setScored(true);

            // Увеличиваем скорость каждые 5 очков
            if (score.getCount() % 5 == 0) {
                float currentSpeed = pipe.getSpeed();
                pipe.setSpeed(currentSpeed - 0.03f); // Увеличиваем скорость (уменьшаем отрицательное значение)
            }
        }
    }

    void resetGame() {
        bird->reset();
        pipe.reset();
        score.reset();
        pipe.setSpeed(-0.05f);
        startTap->reset();
        gameState = GameState::Start;
    }

    void render() {
        window.clear();
        window.draw(background);
        
        if (gameState == GameState::Playing || gameState == GameState::GameOver) {
            pipe.draw(window);
        }
        
        bird->draw(window);
        score.draw(window);
        
        if (gameState == GameState::Start) {
            startTap->draw(window);
        } else if (gameState == GameState::GameOver) {
            window.draw(gameOverScreen);
        }
        
        window.display();
    }
};

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
