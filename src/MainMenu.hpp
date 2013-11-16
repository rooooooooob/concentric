#ifndef CON_MENU_HPP
#define CON_MENU_HPP

#include "Level.hpp"
#include "Game.hpp"
#include "Window.hpp"

namespace con
{

class Menu : public je::Level
{
    public:
        Menu (je::Game* game);
        void drawGUI(sf::RenderTarget& target) const override;
        void onUpdate() override;
        void onDraw(sf::RenderTarget& target) const override;

    private:
        Window start;
};

}
#endif
