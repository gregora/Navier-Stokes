#if !defined _ARROW_H
#define	_ARROW_H 1


#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


class Arrow : public sf::Transformable, public sf::Drawable {

	public:
		float x = 0;
		float y = 0;

		float angle = 0;

		Arrow();

        void setOpacity(uint8_t opacity);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Color color;
		uint8_t r, g, b = 255;
        sf::RectangleShape line;
        sf::ConvexShape head;
};

#endif