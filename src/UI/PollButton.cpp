#include "UI/PollButton.hpp"
#include <iostream>

const int ACTIONS = 8;

namespace con
{

PollButton::PollButton(const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, std::function <void(Button*)> click, std::string texturepath, PlayerConfig& config, Window *window) :
	Button (pos, dimensions, label, level, click, texturepath, window),
	config(config),
	previous (je::Controller::Bind (sf::Keyboard::Key::Space))
{

}

void PollButton::update()
{
	if (input.isButtonPressed(sf::Mouse::Button::Left) && (sf::FloatRect(pos, dimensions).contains(level->getCursorPos())))
	{
		onClick(this);
	}
	else if (polling)
	{
		std::string actions[ACTIONS] = {
			"swing",
			"thrust",
			"throw",
			"jump",
			"crouch",
			"sprint",
			"move_right",
			"move_left",
		};
		
		unsigned int joyID;
		if (input.findController(joyID))
		{
			config.controller.setJoystickID(joyID);
		}
		
		if (pollPos < ACTIONS)
		{
			label = actions[pollPos];
			je::Controller::Bind b(config.controller.getLastInputAsBind());
			if (b.device != je::Controller::Bind::Device::Invalid)
			{
				config.controller.setKeybinds(actions[pollPos], {b});
				//std::cout << actions[pollPos] << ": " << b.key << "\n";
				std::cout << pollPos << "\n";

				++pollPos;
			}
		}
		else if (pollPos == ACTIONS)
		{
			label = "Aim right (left click for mouse aim)";
			je::Controller::AxisBind bind(config.controller.getLastAxisMovementAsBind());
			if (bind.device != je::Controller::AxisBind::Device::Invalid)
			{
				config.controller.setAxis("aim_x", bind);
				++pollPos;
			}
			else if (input.isButtonPressed(sf::Mouse::Button::Left))
			{
				config.controller.setAxis("aim_x", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::X, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
				++pollPos;
			}
		}
		else if (pollPos == ACTIONS + 1)
		{
			label = "Aim Down (left click for mouse aim)";
			je::Controller::AxisBind bind(config.controller.getLastAxisMovementAsBind());
			if (bind.device != je::Controller::AxisBind::Device::Invalid)
			{
				config.controller.setAxis("aim_y", bind);
				++pollPos;
			}
			else if (input.isButtonPressed(sf::Mouse::Button::Left))
			{
				config.controller.setAxis("aim_y", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::Y, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
				++pollPos;
			}
		}
		else
		{
			pollPos = 0;
			polling = false;
			label = "P1 Controls";
		}
	}
}

}
