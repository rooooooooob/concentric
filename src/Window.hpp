#ifndef CON_WINDOW_HPP
#define CON_WINDOW_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

namespace con
{

class Button;

class Window
{

	public:
		Window (const sf::Vector2f &pos, const sf::Vector2f &dimensions, je::Level *level, sf::Color color = sf::Color (200, 200, 200));
		void update();
		void draw(sf::RenderTarget& target, const sf::RenderStates &states = sf::RenderStates::Default) const;
		void open();
		std::vector<Button> buttons;
		sf::RectangleShape frame;
        sf::Color color;
};
}

#endif
