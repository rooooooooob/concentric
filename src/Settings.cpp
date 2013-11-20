#include "Settings.hpp"

namespace con
{

Settings::Settings(je::Game& game)
	:configs()
	,game(game)
{
}

PlayerConfig& Settings::getPlayerConfig(int playerIndex)
{
	return configs[playerIndex];
}

const PlayerConfig& Settings::getPlayerConfig(int playerIndex) const
{
	return configs[playerIndex];
}

void Settings::addPlayer()
{
	configs.push_back(PlayerConfig(
		PlayerConfig::Sword::Katana,
		PlayerConfig::Thrown::Shuriken,
		PlayerConfig::Type::Ninja,
		(int) configs.size(),//default to teams 0,1,2...
		je::Controller(game.getInput(), configs.size() - 1)//so gamepads get used in order 0,1,2...
	));
	je::Controller& input = configs.back().controller;
	if (configs.size() > 1)
	{
		//	default XBOX 360 controls
		input.addKeybind("move_right", je::Controller::Bind(sf::Joystick::Axis::X));
		input.addKeybind("move_left", je::Controller::Bind(sf::Joystick::Axis::X, true));
		input.addKeybind("jump", je::Controller::Bind(4));
		input.addKeybind("jump", je::Controller::Bind(sf::Joystick::Axis::Y, true));
		input.addKeybind("swing", je::Controller::Bind(sf::Joystick::Axis::Z, true));
		input.addKeybind("throw", je::Controller::Bind(5));

		input.setAxis("aim_x", je::Controller::AxisBind(sf::Joystick::Axis::U));
		input.setAxis("aim_y", je::Controller::AxisBind(sf::Joystick::Axis::R));
		configs.back().thrown = PlayerConfig::Thrown::Knife;
		configs.back().type = PlayerConfig::Type::Samurai;
	}
	else
	{
		//	default PC controls
		input.addKeybind("move_left", je::Controller::Bind(sf::Keyboard::Key::A));
		input.addKeybind("move_right", je::Controller::Bind(sf::Keyboard::Key::D));
		input.addKeybind("jump", je::Controller::Bind(sf::Keyboard::Key::W));
		input.addKeybind("swing", je::Controller::Bind(sf::Mouse::Button::Left));
		input.addKeybind("throw", je::Controller::Bind(sf::Mouse::Button::Right));

		input.setAxis("aim_x", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::X, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
		input.setAxis("aim_y", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::Y, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
	}
}

int Settings::getNumberOfPlayers() const
{
	return configs.size();
}

}
