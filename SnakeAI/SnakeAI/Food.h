#pragma once
#include <SFML/Graphics.hpp>

class Food
{
public:
    Food();

    void draw(sf::RenderWindow& window);
    void respawn();

    sf::Vector2i getPosition() const;

private:
    sf::Vector2i position;
    int cellSize;
};