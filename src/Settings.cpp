#include "Settings.hpp"

#include "jam-engine/Core/GamepadPredefs.hpp"

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

void Settings::defaultControlsX360(je::Controller& input)
{
	input.addKeybind("move_right", je::Controller::Bind(sf::Joystick::Axis::X));
	input.addKeybind("move_left", je::Controller::Bind(sf::Joystick::Axis::X, true));
	input.addKeybind("sprint", je::Binds::X360::B);
	input.setKeybinds("jump", {
		je::Binds::X360::DPadUp,
		//je::Binds::X360::LStickUp, //disabled since annoying as fuck
		je::Binds::X360::A,
		je::Binds::X360::LB
	});
	input.setKeybinds("crouch", {
		je::Binds::X360::DPadDown,
		je::Binds::X360::LStickDown
	});
	input.addKeybind("swing", je::Binds::X360::RT);
	input.addKeybind("throw", je::Binds::X360::RB);

	input.setAxis("aim_x", je::Controller::AxisBind(sf::Joystick::Axis::U));
	input.setAxis("aim_y", je::Controller::AxisBind(sf::Joystick::Axis::R));
}

void Settings::defaultControlsPS3(je::Controller& input)
{
	input.addKeybind("move_right", je::Controller::Bind(sf::Joystick::Axis::X));
	input.addKeybind("move_left", je::Controller::Bind(sf::Joystick::Axis::X, true));
	input.addKeybind("sprint", je::Controller::Bind(6)); // I think this is L2? Rebind this to O when you find out what that bind is
	input.setKeybinds("jump", {
		je::Controller::Bind(4),
		je::Controller::Bind(sf::Joystick::Axis::Y, true)
	});
	input.addKeybind("crouch", je::Controller::Bind(sf::Joystick::Axis::Y));
	input.addKeybind("swing", je::Controller::Bind(7));
	input.addKeybind("throw", je::Controller::Bind(5));

	input.setAxis("aim_x", je::Controller::AxisBind(sf::Joystick::Axis::Z));
	input.setAxis("aim_y", je::Controller::AxisBind(sf::Joystick::Axis::R));
}


void Settings::defaultControlsPC(je::Controller& input)
{
	input.addKeybind("move_left", je::Controller::Bind(sf::Keyboard::Key::A));
	input.addKeybind("move_right", je::Controller::Bind(sf::Keyboard::Key::D));
	input.addKeybind("sprint", je::Controller::Bind(sf::Keyboard::Key::LShift));
	input.addKeybind("jump", je::Controller::Bind(sf::Keyboard::Key::W));
	input.addKeybind("crouch", je::Controller::Bind(sf::Keyboard::Key::S));
	input.addKeybind("swing", je::Controller::Bind(sf::Mouse::Button::Left));
	input.addKeybind("throw", je::Controller::Bind(sf::Mouse::Button::Right));

	input.setAxis("aim_x", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::X, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
	input.setAxis("aim_y", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::Y, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
}

void Settings::addPlayer()
{
	configs.push_back(PlayerConfig(
		PlayerConfig::Sword::Katana,
		PlayerConfig::Thrown::Shuriken,
		PlayerConfig::Type::Ninja,
		(int) configs.size(),//default to teams 0,1,2...
		je::Controller(game.getInput(), configs.size() - 1),//so gamepads get used in order 0,1,2...
		(int) configs.size()//player ID 0, 1, 2...
	));
	if (configs.size() > 1)
	{
		defaultControlsX360(configs.back().controller);
		configs.back().thrown = PlayerConfig::Thrown::Knife;
	}
	else
	{
		defaultControlsPC(configs.back().controller);
		configs.back().type = PlayerConfig::Type::Samurai;
	}
}

void Settings::removePlayer()
{
	configs.pop_back();
}

int Settings::getNumberOfPlayers() const
{
	return configs.size();
}

}
