#include "MainMenu.hpp"
#include "Button.hpp"
#include "Arena.hpp"
#include "Controller.hpp"
#include <iostream>

namespace con
{

Menu::Menu (je::Game *game, Settings &settings) :
    je::Level(game, 640, 480),
    settings (settings)
{
    sf::IntRect dimensions= this->getCameraBounds();

    std::vector<Window*> &windowsref = windows;
    Window *start = new Window (sf::Vector2f (0, 0), sf::Vector2f (640, 480), this, sf::Color::Black);
    windows.push_back (start);

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
                                            windows.push_back(w);
                                        },
                                        "start.png", settingswindow));

    settingswindow->buttons.push_back (Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
                                       sf::Vector2f (100, 50), "", this,
                                        [&](je::Level* l, Window* w)
                                        {
                                          //  je::Input& input = level->getInput();
                                           // settings.getLastInputAsBind()
                                        },
                                        "start.png"));
}

void Menu::drawGUI(sf::RenderTarget& target) const
{

}

void Menu::onUpdate()
{
    for (Window *window : windows)
        window->update();
}

void Menu::onDraw(sf::RenderTarget& target) const
{
    for (Window *window : windows)
        window->draw(target);
}

}
