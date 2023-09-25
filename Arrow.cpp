#include "Arrow.h"

Arrow::Arrow() {
    line.setFillColor(sf::Color::Red);
    line.setSize(sf::Vector2f(2, 10));
    line.setOrigin(1, 5);
    line.setPosition(0, 0);

    head = sf::CircleShape(5, 3);

    head.setFillColor(sf::Color::Red);
    head.setOrigin(5, 5);
    head.setPosition(1, -5);
}

void Arrow::setOpacity(uint8_t opacity){
    line.setFillColor(sf::Color(255, 0, 0, opacity));
    head.setFillColor(sf::Color(255, 0, 0, opacity));
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(line, states);
    target.draw(head, states);
}