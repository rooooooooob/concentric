#include "Window.hpp"

namespace con
{

Window::Window (const sf::Vector2f &pos, const sf::Vector2f &dimensions, je::Level *level, sf::Color color) :
    frame (dimensions)
{
    frame.setPosition (pos);
    frame.setFillColor (color);
}

void Window::draw (sf::RenderTarget& target, const sf::RenderStates &states) const
{
    target.draw (frame, states);
    for (Button b : buttons)
    {
        b.draw (target, states);
    }
}

void Window::update ()
{

}

void Window::open ()
{

}

}
