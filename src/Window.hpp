#ifndef CON_WINDOW_HPP
#define CON_WINDOW_HPP

#include <vector>
#include "Button.hpp"

namespace con
{

class Window
{

	public:
		Window (const sf::Vector2f &pos, const sf::Vector2f &dimensions, je::Level *level, sf::Color color = sf::Color (200, 200, 200));
		void update();
		void draw(sf::RenderTarget& target, const sf::RenderStates &states = sf::RenderStates::Default) const;
		bool isOpen() const;
		void toggle();
		std::vector<Button> buttons;

    private:
		sf::RectangleShape frame;
        sf::Color color;
        bool open;
};
}

#endif
