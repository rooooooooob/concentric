#include "PollButton.hpp"
#include <iostream>

namespace con
{

PollButton::PollButton (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, std::function <void(Button*)> click, std::string texturepath, PlayerConfig& config, Window *window) :
	Button (pos, dimensions, label, level, click, texturepath, window),
	config(config)
{

}

void PollButton::update ()
{
	std::cout << "in pollbutton's update";
    if (input.isButtonPressed (sf::Mouse::Button::Left) && (sf::FloatRect (pos, dimensions).contains(level->getCursorPos())))
    {
        onClick (this);
    }

    if (polling)
	{
		std::cout << "polling";
		std::string actions [5] = {"jump", "move_right", "move_left", "swing", "throw"};
		label = actions[pollPos];
		je::Controller::Bind b(config.controller.getLastInputAsBind());
		if (b.device != je::Controller::Bind::Device::Invalid)
		{
			config.controller.setKeybinds(actions[pollPos], {b});
			std::cout << actions[pollPos] << ": " << b.key << "\n";
			if (pollPos == 4)
			{
				pollPos = 0;
			}
			else
				pollPos++;
		}
	}
}

}
