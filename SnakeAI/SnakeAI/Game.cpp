#include "Game.h"
#include <string>
#include <iostream>
#include <fstream>

// Constructorul jocului.
// Inițializează fereastra, meniul, texturile și variabilele.
Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "Snake Legends"),
    scoreText(font),
    gameOverText(font),
    restartText(font),
    homeText(font),
    miniHomeText(font),
    helpTitleText(font),
    helpBodyText(font),
    highScoreText(font)
{
    moveDelay = 0.15f;
    score = 0;
    highScore = 0;
    loadHighScore();
    gameOver = false;
    wallHitEffect = false;
    showHelp = false;
    state = GameState::Menu;

    font.openFromFile("C:/Windows/Fonts/consolab.ttf");

    sf::Image icon;
    if (icon.loadFromFile("assets/images/snakeLogo.png"))
        window.setIcon(icon);

    menuBackgroundTexture.loadFromFile("assets/images/menu_background.png");
    logoTexture.loadFromFile("assets/images/logo_snake_legends.png");
    mascotTexture.loadFromFile("assets/images/snake_mascot.png");
    playButtonTexture.loadFromFile("assets/images/button_play.png");
    aiButtonTexture.loadFromFile("assets/images/button_ai.png");
    exitButtonTexture.loadFromFile("assets/images/button_exit.png");
    helpButtonTexture.loadFromFile("assets/images/button_help.png");

    menuBackgroundSprite.setTexture(menuBackgroundTexture, true);
    logoSprite.setTexture(logoTexture, true);
    mascotSprite.setTexture(mascotTexture, true);
    playButtonSprite.setTexture(playButtonTexture, true);
    aiButtonSprite.setTexture(aiButtonTexture, true);
    exitButtonSprite.setTexture(exitButtonTexture, true);
    helpButtonSprite.setTexture(helpButtonTexture, true);

    logoSprite.setPosition({ 140.f, 25.f });
    logoSprite.setScale({ 1.0f, 1.0f });

    mascotSprite.setPosition({ 70.f, 330.f });
    mascotSprite.setScale({ 1.0f, 1.0f });

    playButtonSprite.setPosition({ 430.f, 230.f });
    aiButtonSprite.setPosition({ 430.f, 315.f });
    exitButtonSprite.setPosition({ 430.f, 400.f });

    helpButtonSprite.setPosition({ 700.f, 520.f });

    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(3);
    scoreText.setPosition({ 20, 15 });

    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::Yellow);
    highScoreText.setOutlineColor(sf::Color::Black);
    highScoreText.setOutlineThickness(2);
    highScoreText.setPosition({ 20, 50 });

    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color(255, 80, 80));
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(5);
    gameOverText.setPosition({ 205, 210 });

    restartButton.setSize({ 220, 70 });
    restartButton.setFillColor(sf::Color(45, 170, 70));
    restartButton.setOutlineColor(sf::Color::Black);
    restartButton.setOutlineThickness(5);
    restartButton.setPosition({ 290, 350 });

    restartText.setString("RESTART  R");
    restartText.setCharacterSize(28);
    restartText.setFillColor(sf::Color::White);
    restartText.setOutlineColor(sf::Color::Black);
    restartText.setOutlineThickness(3);
    restartText.setPosition({ 315, 368 });

    homeButton.setSize({ 220, 70 });
    homeButton.setFillColor(sf::Color(45, 130, 170));
    homeButton.setOutlineColor(sf::Color::Black);
    homeButton.setOutlineThickness(5);
    homeButton.setPosition({ 290, 440 });

    homeText.setString("HOME  ESC");
    homeText.setCharacterSize(28);
    homeText.setFillColor(sf::Color::White);
    homeText.setOutlineColor(sf::Color::Black);
    homeText.setOutlineThickness(3);
    homeText.setPosition({ 325, 458 });

    miniHomeButton.setSize({ 120, 40 });
    miniHomeButton.setFillColor(sf::Color(45, 130, 170));
    miniHomeButton.setOutlineColor(sf::Color::Black);
    miniHomeButton.setOutlineThickness(3);
    miniHomeButton.setPosition({ 660, 15 });

    miniHomeText.setString("HOME");
    miniHomeText.setCharacterSize(20);
    miniHomeText.setFillColor(sf::Color::White);
    miniHomeText.setOutlineColor(sf::Color::Black);
    miniHomeText.setOutlineThickness(2);
    miniHomeText.setPosition({ 690, 22 });

    helpPanel.setSize({ 620, 330 });
    helpPanel.setFillColor(sf::Color(20, 45, 30, 235));
    helpPanel.setOutlineColor(sf::Color::Black);
    helpPanel.setOutlineThickness(5);
    helpPanel.setPosition({ 90, 140 });

    helpTitleText.setString("HOW TO PLAY");
    helpTitleText.setCharacterSize(36);
    helpTitleText.setFillColor(sf::Color(230, 255, 180));
    helpTitleText.setOutlineColor(sf::Color::Black);
    helpTitleText.setOutlineThickness(3);
    helpTitleText.setPosition({ 265, 165 });

    helpBodyText.setString(
        "SINGLE PLAYER:\n"
        "- Foloseste sagetile pentru miscare.\n"
        "- Mananca fructe pentru scor.\n"
        "- Daca lovesti peretele sau corpul pierzi segment.\n\n"
        "AI MODE:\n"
        "- Modul AI va folosi algoritmi precum BFS / A*.\n"
        "- Sarpele va cauta automat drumul catre fruct.\n\n"
        "Apasa ? din nou pentru inchidere."
    );
    helpBodyText.setCharacterSize(20);
    helpBodyText.setFillColor(sf::Color::White);
    helpBodyText.setPosition({ 125, 225 });

    updateScoreText();
}

// Bucla principală a jocului.
// Rulează continuu până când utilizatorul închide aplicația.
void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

// Gestionează evenimentele utilizatorului.
// Tastatură, mouse și închiderea ferestrei.
void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (state == GameState::Playing &&
                keyPressed->code == sf::Keyboard::Key::Escape)
            {
                restartGame();
                state = GameState::Menu;
                return;
            }

            if (gameOver &&
                (keyPressed->code == sf::Keyboard::Key::R ||
                    keyPressed->code == sf::Keyboard::Key::Enter))
            {
                restartGame();
                state = GameState::Playing;
            }

            if (gameOver && keyPressed->code == sf::Keyboard::Key::Escape)
            {
                restartGame();
                state = GameState::Menu;
            }

            if (!gameOver && state == GameState::Playing)
            {
                if (keyPressed->code == sf::Keyboard::Key::Up)
                    snake.setDirection(Direction::Up);
                else if (keyPressed->code == sf::Keyboard::Key::Down)
                    snake.setDirection(Direction::Down);
                else if (keyPressed->code == sf::Keyboard::Key::Left)
                    snake.setDirection(Direction::Left);
                else if (keyPressed->code == sf::Keyboard::Key::Right)
                    snake.setDirection(Direction::Right);
            }
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePos(
                    static_cast<float>(mousePressed->position.x),
                    static_cast<float>(mousePressed->position.y)
                );

                if (state == GameState::Menu)
                {
                    handleMenuClick(mousePos);
                }
                else if (state == GameState::Playing && !gameOver)
                {
                    if (miniHomeButton.getGlobalBounds().contains(mousePos))
                    {
                        restartGame();
                        state = GameState::Menu;
                        return;
                    }
                }
                else if (gameOver)
                {
                    if (restartButton.getGlobalBounds().contains(mousePos))
                    {
                        restartGame();
                        state = GameState::Playing;
                    }

                    if (homeButton.getGlobalBounds().contains(mousePos))
                    {
                        restartGame();
                        state = GameState::Menu;
                    }
                }
            }
        }
    }
}

// Actualizează logica jocului.
// Mișcare, coliziuni și colectarea hranei.
void Game::update()
{
    if (state == GameState::Menu)
        return;

    if (gameOver)
        return;

    if (clock.getElapsedTime().asSeconds() >= moveDelay)
    {
        snake.move();

        if (snake.hitWall())
        {
            snake.bounceBack();
            snake.removeSegment();

            wallHitEffect = true;
            wallHitClock.restart();

            if (snake.getSize() <= 1)
            {
                checkAndSaveHighScore();
                gameOver = true;
                window.setTitle("Snake Legends - GAME OVER - Score: " + std::to_string(score));
                return;
            }
        }

        if (snake.hitSelf())
        {
            snake.bounceBack();
            snake.removeSegment();

            wallHitEffect = true;
            wallHitClock.restart();

            if (snake.getSize() <= 1)
            {
                checkAndSaveHighScore();
                gameOver = true;
                window.setTitle("Snake Legends - GAME OVER - Score: " + std::to_string(score));
                return;
            }
        }

        if (snake.getHeadPosition() == food.getPosition())
        {
            snake.grow();
            food.respawn();

            score += 10;
            updateScoreText();

            window.setTitle("Snake Legends - Score: " + std::to_string(score));
        }

        clock.restart();
    }
}

// Decide ce se afișează pe ecran.
// Meniu sau joc.
void Game::render()
{
    if (state == GameState::Menu)
        renderMenu();
    else
        renderGame();
}

// Desenează meniul principal și elementele grafice.
void Game::renderMenu()
{
    window.clear();

    window.draw(menuBackgroundSprite);
    window.draw(logoSprite);
    window.draw(mascotSprite);

    window.draw(playButtonSprite);
    window.draw(aiButtonSprite);
    window.draw(exitButtonSprite);
    window.draw(helpButtonSprite);

    if (showHelp)
    {
        window.draw(helpPanel);
        window.draw(helpTitleText);
        window.draw(helpBodyText);
    }

    window.display();
}

// Desenează toate elementele din timpul jocului.
void Game::renderGame()
{
    if (wallHitEffect && wallHitClock.getElapsedTime().asSeconds() < 0.15f)
        window.clear(sf::Color(120, 20, 20));
    else
    {
        wallHitEffect = false;
        window.clear(sf::Color(25, 25, 25));
    }

    snake.draw(window);
    food.draw(window);

    window.draw(scoreText);
    window.draw(highScoreText);
    window.draw(miniHomeButton);
    window.draw(miniHomeText);

    if (gameOver)
    {
        window.draw(gameOverText);

        window.draw(restartButton);
        window.draw(restartText);

        window.draw(homeButton);
        window.draw(homeText);
    }

    window.display();
}

// Procesează apăsarea butoanelor din meniu.
void Game::handleMenuClick(sf::Vector2f mousePos)
{
    if (playButtonSprite.getGlobalBounds().contains(mousePos))
    {
        restartGame();
        state = GameState::Playing;
    }

    if (aiButtonSprite.getGlobalBounds().contains(mousePos))
    {
        restartGame();
        state = GameState::Playing;
        window.setTitle("Snake Legends - AI Mode coming soon");
    }

    if (exitButtonSprite.getGlobalBounds().contains(mousePos))
    {
        window.close();
    }

    if (helpButtonSprite.getGlobalBounds().contains(mousePos))
    {
        showHelp = !showHelp;
    }
}

// Resetează jocul la starea inițială.
void Game::restartGame()
{
    snake.reset();
    food.respawn();

    score = 0;
    gameOver = false;
    wallHitEffect = false;

    updateScoreText();

    window.setTitle("Snake Legends");
    clock.restart();
}

// Actualizează afișarea scorului și a recordului.
void Game::updateScoreText()
{
    scoreText.setString("SCORE: " + std::to_string(score));
    highScoreText.setString("BEST: " + std::to_string(highScore));
}

// Încarcă recordul din fișier.
void Game::loadHighScore()
{
    std::ifstream file("highscore.txt");

    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    else
    {
        highScore = 0;
    }
}

// Salvează recordul în fișier.
void Game::saveHighScore()
{
    std::ofstream file("highscore.txt");

    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

// Verifică dacă scorul actual depășește recordul.
void Game::checkAndSaveHighScore()
{
    if (score > highScore)
    {
        highScore = score;
        saveHighScore();
        updateScoreText();
    }
}