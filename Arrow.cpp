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

    head = sf::ConvexShape(3);
    head.setPoint(0, sf::Vector2f(0, 0));
    head.setPoint(1, sf::Vector2f(2.5, -5));
    head.setPoint(2, sf::Vector2f(5, 0));

    head.setFillColor(color);
    head.setOrigin(2.5, 0);
    head.setPosition(0, -5);
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