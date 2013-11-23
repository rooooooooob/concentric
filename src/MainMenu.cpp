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

	start->buttons.push_back(std::unique_ptr<Button>(new Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
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

	settingswindow->buttons.push_back (std::unique_ptr<Button>(new Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
		sf::Vector2f (100, 50), "Add player", this,
		[&](Button *b)
		{
			settings.addPlayer();
			settingswindow->buttons.push_back (std::unique_ptr<Button>(new PollButton (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
				sf::Vector2f (100, 50), std::string("P") + (char)('0' + settings.getNumberOfPlayers()) + std::string(" Controls"), this,
				[&](Button *b)
				{
					b->setPolling(true);
				},
				"start.png", settings.getPlayerConfig(settings.getNumberOfPlayers() - 1))));
		},
		"start.png")));
	
	settingswindow->buttons.push_back (std::unique_ptr<Button>(new Button (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
		sf::Vector2f (100, 50), "Remove player", this,
		[&](Button *b)
		{
			
		},
		"start.png")));
	
	settingswindow->buttons.push_back (std::unique_ptr<Button> (new Button (sf::Vector2f((dimensions.width/2) - 50, (dimensions.height/2) + 50),
		sf::Vector2f (100, 50), "Back", this,
		[&](Button *b)
		{
			current = start;
		},
		"start.png")));

	for (int i = 0; i < settings.getNumberOfPlayers(); ++i)
	{
		settingswindow->buttons.push_back (std::unique_ptr<Button>(new PollButton (sf::Vector2f ((dimensions.width/2) - 50, (dimensions.height/2) - 25),
			sf::Vector2f (100, 50), std::string("P") + (char)('0' + settings.getNumberOfPlayers()) + std::string(" Controls"), this,
			[&](Button *b)
			{
				b->setPolling(true);
			},
			"start.png", settings.getPlayerConfig(i))));
	}



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
