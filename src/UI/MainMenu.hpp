#ifndef CON_MENU_HPP
#define CON_MENU_HPP

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "UI/Window.hpp"
#include "Settings.hpp"
#include <vector>
#include <functional>

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
	void addPlayer();
	void removePlayer();

	Window *start;
	Window *current;
	Settings &settings;
	bool isUpdating;
	Window *settingswindow;
	std::vector<std::function<void()> > callLater;
};

}
#endif
