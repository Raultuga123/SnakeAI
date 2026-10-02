#include "Snake.h"

// Constructorul șarpelui.
// Creează poziția inițială și direcția.
Snake::Snake()
{
    cellSize = 25;
    direction = Direction::Right;

    body.push_back({ 10, 10 });
    body.push_back({ 9, 10 });
    body.push_back({ 8, 10 });
}

// Schimbă direcția de deplasare.
void Snake::setDirection(Direction newDirection)
{
    if (direction == Direction::Up && newDirection == Direction::Down)
        return;
    if (direction == Direction::Down && newDirection == Direction::Up)
        return;
    if (direction == Direction::Left && newDirection == Direction::Right)
        return;
    if (direction == Direction::Right && newDirection == Direction::Left)
        return;

    direction = newDirection;
}

// Deplasează șarpele pe hartă.
void Snake::move()
{
    sf::Vector2i newHead = body.front();

    if (direction == Direction::Up)
        newHead.y--;
    else if (direction == Direction::Down)
        newHead.y++;
    else if (direction == Direction::Left)
        newHead.x--;
    else if (direction == Direction::Right)
        newHead.x++;

    body.insert(body.begin(), newHead);
    body.pop_back();
}

// Adaugă un segment nou șarpelui.
void Snake::grow()
{
    body.push_back(body.back());
}

// Elimină un segment după coliziune.
void Snake::removeSegment()
{
    if (body.size() > 1)
        body.pop_back();
}

// Împinge șarpele înapoi după impact.
void Snake::bounceBack()
{
    if (direction == Direction::Up)
        body.front().y++;
    else if (direction == Direction::Down)
        body.front().y--;
    else if (direction == Direction::Left)
        body.front().x++;
    else if (direction == Direction::Right)
        body.front().x--;
}

// Reface șarpele la starea inițială.
void Snake::reset()
{
    body.clear();

    direction = Direction::Right;

    body.push_back({ 10, 10 });
    body.push_back({ 9, 10 });
    body.push_back({ 8, 10 });
}

// Desenează șarpele pe ecran.
void Snake::draw(sf::RenderWindow& window)
{
    sf::RectangleShape segment;
    segment.setSize(sf::Vector2f(cellSize - 2, cellSize - 2));

    for (size_t i = 0; i < body.size(); i++)
    {
        if (i == 0)
            segment.setFillColor(sf::Color(120, 255, 120));
        else
            segment.setFillColor(sf::Color(50, 200, 70));

        segment.setPosition(sf::Vector2f(
            body[i].x * cellSize,
            body[i].y * cellSize
        ));

        window.draw(segment);
    }
}

// Returnează poziția capului șarpelui.
sf::Vector2i Snake::getHeadPosition() const
{
    return body.front();
}

// Returnează lungimea șarpelui.
int Snake::getSize() const
{
    return static_cast<int>(body.size());
}

// Verifică dacă șarpele lovește peretele.
bool Snake::hitWall() const
{
    sf::Vector2i head = body.front();

    int columns = 800 / cellSize;
    int rows = 600 / cellSize;

    return head.x < 0 || head.x >= columns ||
        head.y < 0 || head.y >= rows;
}

// Verifică dacă șarpele se lovește de propriul corp.
bool Snake::hitSelf() const
{
    sf::Vector2i head = body.front();

    for (size_t i = 1; i < body.size(); i++)
    {
        if (body[i] == head)
            return true;
    }

    return false;
}