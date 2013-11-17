#include "Window.hpp"

namespace con
{

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
    for (Button b : buttons)
    {
        b.draw (target, states);
    }
}

void Window::update ()
{
    for (Button b : buttons)
    {
        b.update();
    }
}

bool Window::isOpen () const
{
    return open;
}

void Window::toggle ()
{
    if (open)
        open = false;
    else
        open = true;
}

}
