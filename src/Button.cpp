#include "Button.hpp"
#include <iostream>

namespace con
{

Button::Button (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, sf::Color color, Window *window) :
    level (level),
    pos (pos),
    dimensions (dimensions),
    window(window),
    frame (dimensions),
    label(label)
{
    frame.setPosition (pos);
    frame.setFillColor (color);
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "can't load fonts\n";
    }
}

void Button::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
    //work around because there's some really weird scope errors with Text
    target.draw (frame, states);
    sf::Text t;

    t.setPosition (pos);
    t.setFont (font);
    t.setString (label);

    target.draw (t, states);
}

}
