#include "Button.hpp"
#include "Game.hpp"
#include <iostream>

namespace con
{

Button::Button (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, std::function <void(je::Level*)> click, std::string texturepath, Window *window) :
    level (level),
    pos (pos),
    dimensions (dimensions),
    frame (dimensions),
    window(window),
    label(label),
    input (level->getGame().getInput()),
    onClick (click),
    texture (level->getGame().getTexManager().get(texturepath))
{
    frame.setPosition (pos);
    frame.setTexture (&texture);
    if (!font.loadFromFile("resources/arial.ttf"))
        std::cout << "can't button load fonts\n";
}

void Button::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
    //work around because there's some really weird scope errors with Text
    sf::RectangleShape mpos (sf::Vector2f (50, 50));
    mpos.setPosition (level->getCursorPos());
    mpos.setFillColor (sf::Color::Blue);

    sf::RectangleShape cpy = frame;
    cpy.setTexture (&texture);
    target.draw (cpy, states);

    sf::Text t;

    t.setPosition (pos);
    t.setFont (font);
    t.setString (label);
    t.setCharacterSize(20);

    target.draw (t, states);

    target.draw (mpos, states);
}

void Button::update ()
{
    if (input.isButtonPressed (sf::Mouse::Button::Left) && (sf::FloatRect (pos, dimensions).contains(level->getCursorPos())))
    {
        onClick (level);
    }
}

}
