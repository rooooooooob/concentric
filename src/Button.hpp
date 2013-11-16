#ifndef CON_BUTTON_HPP
#define CON_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "Level.hpp"

namespace con
{

class Window;

class Button
{
	public:
		Button (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, sf::Color color = sf::Color (100, 100, 100), Window *window = nullptr);
		void draw(sf::RenderTarget& target, const sf::RenderStates &states = sf::RenderStates::Default) const;
		sf::RectangleShape frame;
		Window* window;

	private:
		je::Level* level;
        sf::Vector2f pos;
        sf::Vector2f dimensions;
        sf::Color color;
        sf::Font font;
        std::string label;
};

}

#endif
