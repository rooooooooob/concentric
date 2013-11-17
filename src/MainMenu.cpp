#include "MainMenu.hpp"
#include "Button.hpp"
#include "Arena.hpp"
#include "Controller.hpp"
#include <iostream>
#include <initializer_list>

namespace con
{

Menu::Menu (je::Game *game, Settings &settings) :
    je::Level(game, 640, 480),
    settings (settings)
{
    start = new Window (sf::Vector2f (0, 0), sf::Vector2f (640, 480), this, sf::Color::Black);
    current = start;
    sf::IntRect dimensions= this->getCameraBounds();

    start->buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "Start", this,
                                        [&](je::Level* l, Window* w)
                                        {
                                            je::Game &g = l->getGame();
                                            g.setLevel (new Arena (&g, settings));
                                        },
                                        "start.png"));

    Window *settingswindow = new Window (sf::Vector2f (0,0), sf::Vector2f (640, 480), this, sf::Color::Black);

    start->buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) + 50),
                                       sf::Vector2f (100, 50), "Settings", this,
                                        [&](je::Level* l, Window* w)
                                        {
                                            current = w;
                                        },
                                        "start.png", settingswindow));

    settingswindow->buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "controls", this,
                                        [&](je::Level* l, Window* w)
                                        {
                                            std::cout << "agdsag";
                                            std::initializer_list<std::string> actions =
                                            {
                                                "jump", "move_right", "move_left", "swing", "throw", "L2", "dpadup",
                                                "dpaddown"
                                            };

											for (int i = 0; i < settings.getNumberOfPlayers(); ++i)
                                            {
												PlayerConfig& config = settings.getPlayerConfig(i);
                                                for (std::string action : actions)
                                                {
                                                    je::Controller::Bind b(config.controller.getLastInputAsBind());
                                                    while (b.device == je::Controller::Bind::Device::Invalid)
                                                    {
                                                        je::Controller::Bind b(config.controller.getLastInputAsBind());
                                                    }
                                                    config.controller.setKeybinds(action, {b});
                                                }
                                            }
                                        },
                                        "start.png"));
}

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
