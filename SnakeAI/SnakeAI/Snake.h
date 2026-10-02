#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class Snake
{
public:
    Snake();

    void move();
    void grow();
    void removeSegment();
    void bounceBack();
    void reset();

    void setDirection(Direction newDirection);
    void draw(sf::RenderWindow& window);

    sf::Vector2i getHeadPosition() const;
    int getSize() const;

    bool hitWall() const;
    bool hitSelf() const;

private:
    std::vector<sf::Vector2i> body;
    Direction direction;
    int cellSize;
};