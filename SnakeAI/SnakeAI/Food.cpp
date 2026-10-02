#include "Food.h"
#include <cstdlib>
#include <ctime>

// Constructorul hranei.
// Generează prima poziție.
Food::Food()
{
    cellSize = 25;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    respawn();
}

// Generează o nouă poziție aleatoare pentru hrană.
void Food::respawn()
{
    int columns = 800 / cellSize;
    int rows = 600 / cellSize;

    position.x = std::rand() % columns;
    position.y = std::rand() % rows;
}

// Desenează hrana pe ecran.
void Food::draw(sf::RenderWindow& window)
{
    sf::RectangleShape food;

    food.setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
    food.setFillColor(sf::Color::Red);
    food.setOutlineColor(sf::Color::Black);
    food.setOutlineThickness(2);

    food.setPosition(sf::Vector2f(
        position.x * cellSize,
        position.y * cellSize
    ));

    window.draw(food);
}

// Returnează poziția hranei.
sf::Vector2i Food::getPosition() const
{
    return position;
}