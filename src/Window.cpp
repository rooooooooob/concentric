#include "Window.hpp"

namespace con
{

Window::Window () :
	frame (sf::Vector2f (0, 0)),
	open (false)
{
	frame.setPosition (0, 0);
	frame.setFillColor (sf::Color::Black);
}

Window::Window (const sf::Vector2f &pos, const sf::Vector2f &dimensions, je::Level *level, sf::Color color) :
	frame (dimensions),
	open (false)
{
	frame.setPosition (pos);
	frame.setFillColor (color);
}

void Window::draw (sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw (frame, states);
	for (auto& b : buttons)
	{
		b->draw (target, states);
	}
}

void Window::update ()
{
	for (auto& b : buttons)
	{
		b->update();
	}
}

bool Window::isOpen () const
{
	return open;
}

void Window::toggle ()
{
	open = !open;
}

}
