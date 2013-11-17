#include "MainMenu.hpp"
#include "Button.hpp"
#include "Arena.hpp"
#include "Controller.hpp"
#include "PollButton.hpp"
#include <iostream>

namespace con
{

Menu::Menu (je::Game *game, Settings &settings) :
    je::Level(game, 640, 480),
    settings (settings)
{
    start = new Window (sf::Vector2f (0, 0), sf::Vector2f (640, 480), this, sf::Color::Black);
    current = start;
    sf::IntRect dimensions= this->getCameraBounds();

    start->buttons.push_back (std::unique_ptr<Button>(new Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "Start", this,
                                        [&](Button* b)
                                        {
                                            je::Game &g = b->getLevel()->getGame();
                                            g.setLevel (new Arena (&g, settings));
                                        },
                                        "start.png")));

    Window *settingswindow = new Window (sf::Vector2f (0,0), sf::Vector2f (640, 480), this, sf::Color::Black);

    start->buttons.push_back(std::unique_ptr<Button>(new Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) + 50),
                                       sf::Vector2f (100, 50), "Settings", this,
                                        [&](Button *b)
                                        {
                                            current = b->getLink();
                                        },
                                        "start.png", settingswindow)));

    settingswindow->buttons.push_back (std::unique_ptr<Button>(new PollButton (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "P1 Controls", this,
                                        [&](Button *b)
                                        {
                                        	b->setPolling(true);
                                        	std::cout << "lambda";
                                        },
                                        "start.png", settings.getPlayerConfig(0))));

   /* settingswindow->buttons.push_back (Button (sf::Vector2f((dimensions.width/2) - 50, (dimensions.height/2) + 50),
                                       sf::Vector2f (100, 50), "Back", this,
                                        [&](Button *b)
                                        {
                                            current = start;
                                        },
                                        "start.png"));

*/}

void Menu::drawGUI(sf::RenderTarget& target) const
{

}

void Menu::onUpdate()
{
    current->update();
}

void Menu::onDraw(sf::RenderTarget& target) const
{
    current->draw(target);
}

}
