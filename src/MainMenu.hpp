#ifndef CON_MENU_HPP
#define CON_MENU_HPP

#include "Level.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Settings.hpp"
#include <vector>

namespace con
{

class Menu : public je::Level
{
    public:
        Menu (je::Game* game, Settings &settings);
        void drawGUI(sf::RenderTarget& target) const override;
        void onUpdate() override;
        void onDraw(sf::RenderTarget& target) const override;

    private:
        Window *start;
        Window *current;
        Settings &settings;

};

}
#endif
