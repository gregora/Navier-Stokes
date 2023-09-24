#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


class Arrow : public sf::Transformable, public sf::Drawable {

	public:
		float x = 0;
		float y = 0;

		float angle = 0;

		Arrow();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
        sf::RectangleShape line;
        sf::CircleShape head;
};