#ifndef CON_BUTTON_HPP
#define CON_BUTTON_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Input.hpp"

namespace con
{

class Window;

class Button
{
	public:
		Button (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, std::function <void(Button*)> click, std::string texturepath, Window *window = nullptr);
		virtual void draw(sf::RenderTarget& target, const sf::RenderStates &states = sf::RenderStates::Default) const;
		virtual void update ();
		const je::Level* getLevel () const;
		Window* getLink () const;
		void setPolling (bool truth);

	protected:
		je::Level* level;
        sf::Vector2f pos;
        sf::Vector2f dimensions;
		sf::RectangleShape frame;
		Window* window;
        std::string label;
		je::Input& input;
        sf::Texture texture;
        std::function<void(Button*)> onClick;
        bool polling;
        int pollPos;
        sf::Font font;
};

}

#endif
