#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void moveLeft(float dt);
    void moveRight(float dt);
    void setWidth(float width);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    float getWidth() const;

private:
    sf::RectangleShape shape;
    float width;
    float height;
    float x, y;
};

#endif

