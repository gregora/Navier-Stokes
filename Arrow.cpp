#include "Arrow.h"

Arrow::Arrow() {
    r = 52;
    g = 79;
    b = 235;
    color = sf::Color(r, g, b);
    line.setFillColor(color);
    line.setSize(sf::Vector2f(2, 10));
    line.setOrigin(1, 5);
    line.setPosition(0, 0);

    head = sf::CircleShape(5, 3);

    head.setFillColor(color);
    head.setOrigin(5, 5);
    head.setPosition(1, -5);
}

void Arrow::setOpacity(uint8_t opacity){
    line.setFillColor(sf::Color(r, g, b, opacity));
    head.setFillColor(sf::Color(r, g, b, opacity));
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(line, states);
    target.draw(head, states);
}