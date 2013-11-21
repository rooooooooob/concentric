#include "PollButton.hpp"
#include <iostream>

namespace con
{

PollButton::PollButton (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, std::function <void(Button*)> click, std::string texturepath, PlayerConfig& config, Window *window) :
	Button (pos, dimensions, label, level, click, texturepath, window),
	config(config),
	previous (je::Controller::Bind (sf::Keyboard::Key::Space))
{

}

void PollButton::update ()
{
    if (input.isButtonReleased (sf::Mouse::Button::Left) && (sf::FloatRect (pos, dimensions).contains(level->getCursorPos())))
    {
        onClick (this);
    }

    if (polling)
	{
		std::string actions [5] = { "jump", "move_right", "move_left", "swing", "throw"};
		label = actions[pollPos];
		unsigned int joyID;
		if (input.findController(joyID))
		{
			config.controller.setJoystickID(joyID);
		}
		je::Controller::Bind b(config.controller.getLastInputAsBind());
		if (b.device != je::Controller::Bind::Device::Invalid)
		{
			config.controller.setKeybinds(actions[pollPos], {b});
			//std::cout << actions[pollPos] << ": " << b.key << "\n";
			std::cout << pollPos << "\n";

			pollPos++;
			if (pollPos == 5)
			{
				pollPos = 0;
				polling = false;
				label = "P1 Controls";
			}
		}
	}
}

}
