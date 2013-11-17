#include "MainMenu.hpp"
#include "Button.hpp"
#include "Arena.hpp"
#include <iostream>

namespace con
{

Menu::Menu (je::Game *game, Settings &settings) :
    je::Level(game, 640, 480),
    start (sf::Vector2f (0, 0), sf::Vector2f (640, 480), this, sf::Color::Black),
    settings (settings)
{
    sf::IntRect dimensions= this->getCameraBounds();
    start.buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "Start", this,
                                        [](je::Level* l)
                                        {
                                            je::Game &g = l->getGame();
                                            g.setLevel (new Arena (&g));
                                        },
                                        "start.png"));

    start.buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) + 50),
                                       sf::Vector2f (100, 50), "Settings", this,
                                        [settings](je::Level* l)
                                        {
                                            je::Game &g = l->getGame();
                                            g.setLevel (new Arena (&g));
                                        },
                                        "start.png"));
}

void Menu::drawGUI(sf::RenderTarget& target) const
{

}

void Menu::onUpdate()
{
    start.update ();
}

void Menu::onDraw(sf::RenderTarget& target) const
{
    start.draw (target);
}

}
