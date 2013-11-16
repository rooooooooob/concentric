#include "MainMenu.hpp"
#include "Button.hpp"

namespace con
{

Menu::Menu (je::Game *game) :
    je::Level(game, 640, 480),
    start (sf::Vector2f (0, 0), sf::Vector2f (640, 480), this, sf::Color::Magenta)
{
    sf::IntRect dimensions= this->getCameraBounds();
    start.buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "Start", this, sf::Color::Red));
}

void Menu::drawGUI(sf::RenderTarget& target) const
{

}

void Menu::onUpdate()
{

}

void Menu::onDraw(sf::RenderTarget& target) const
{
    start.draw (target);
}

}
