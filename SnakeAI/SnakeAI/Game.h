#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

enum class GameState
{
    Menu,
    Playing
};

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Snake snake;
    Food food;

    GameState state;

    sf::Clock clock;
    sf::Clock wallHitClock;

    sf::Font font;

    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text gameOverText;
    sf::Text restartText;
    sf::Text homeText;
    sf::Text miniHomeText;
    sf::Text helpTitleText;
    sf::Text helpBodyText;

    sf::RectangleShape restartButton;
    sf::RectangleShape homeButton;
    sf::RectangleShape miniHomeButton;
    sf::RectangleShape helpPanel;

    sf::Texture menuBackgroundTexture;
    sf::Texture logoTexture;
    sf::Texture mascotTexture;
    sf::Texture playButtonTexture;
    sf::Texture aiButtonTexture;
    sf::Texture exitButtonTexture;
    sf::Texture helpButtonTexture;

    sf::Sprite menuBackgroundSprite{ menuBackgroundTexture };
    sf::Sprite logoSprite{ logoTexture };
    sf::Sprite mascotSprite{ mascotTexture };
    sf::Sprite playButtonSprite{ playButtonTexture };
    sf::Sprite aiButtonSprite{ aiButtonTexture };
    sf::Sprite exitButtonSprite{ exitButtonTexture };
    sf::Sprite helpButtonSprite{ helpButtonTexture };

    float moveDelay;
    int score;
    int highScore;

    bool gameOver;
    bool wallHitEffect;
    bool showHelp;

    void processEvents();
    void update();
    void render();

    void renderMenu();
    void renderGame();

    void restartGame();
    void updateScoreText();
    void handleMenuClick(sf::Vector2f mousePos);

    void loadHighScore();
    void saveHighScore();
    void checkAndSaveHighScore();
};