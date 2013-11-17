#include "Arena.hpp"
#include "Game.hpp"

#include <cstdlib>
#include "Game.hpp"
#include "SolidGround.hpp"
#include "Scenery.hpp"

#include "Controller.hpp"
#include "PlayerConfig.hpp"
#include "Player.hpp"

namespace con
{

Arena::Arena(je::Game *game)
	:je::Level(game, 640, 480)
{
	for (int i = 0; i < getWidth(); i += 32)
	{
		for (int j = 1; j < 4; ++j)
			addEntity(new SolidGround(this, i, getHeight() - j * 32, sf::Rect<int>(i, getHeight() - j * 32, 32, 32), "dirt.png"));
		Scenery *grass = new Scenery(this, i, getHeight() - 3 * 32 - 6, (rand() % 2 ? "grass0.png" : "grass1.png"));
		grass->setDepth(-10);
		addEntity(grass);
	}

	PlayerConfig p1config = {
		PlayerConfig::Sword::Katana,
		PlayerConfig::Thrown::Shuriken,
		PlayerConfig::Type::Ninja,
		je::Controller(getGame().getInput(), 0)
	};

	je::Controller& p1controls = p1config.controller;
	p1controls.addKeybind("jump", je::Controller::Bind(4));
	p1controls.addKeybind("jump", je::Controller::Bind(sf::Joystick::Axis::Y, true));
	p1controls.addKeybind("move_right", je::Controller::Bind(sf::Joystick::Axis::X));
	p1controls.addKeybind("move_left", je::Controller::Bind(sf::Joystick::Axis::X, true));
	p1controls.addKeybind("move_left", je::Controller::Bind(sf::Keyboard::Key::A));
	p1controls.addKeybind("move_right", je::Controller::Bind(sf::Keyboard::Key::D));
	p1controls.addKeybind("jump", je::Controller::Bind(sf::Keyboard::Key::W));
	p1controls.addKeybind("swing", je::Controller::Bind(sf::Joystick::Axis::Z, true));
	p1controls.addKeybind("throw", je::Controller::Bind(5));
	p1controls.addKeybind("L2", je::Controller::Bind(sf::Joystick::Axis::Z));
	p1controls.addKeybind("dpadup", je::Controller::Bind(sf::Joystick::Axis::PovX));
	p1controls.addKeybind("dpaddown", je::Controller::Bind(sf::Joystick::Axis::PovX, true));
	p1controls.addKeybind("dpadright", je::Controller::Bind(sf::Joystick::Axis::PovY));
	p1controls.addKeybind("dpadleft", je::Controller::Bind(sf::Joystick::Axis::PovY, true));
	// axis = R = up to down
	// axis = U = left to right
	p1controls.addKeybind("A", je::Controller::Bind(0));
	p1controls.addKeybind("B", je::Controller::Bind(1));
	p1controls.addKeybind("X", je::Controller::Bind(2));
	p1controls.addKeybind("Y", je::Controller::Bind(3));
	//left joy in = 8, right = 9
	//select 6 start 7
	p1controls.setAxis("aim_x", je::Controller::AxisBind(sf::Joystick::Axis::U));
	p1controls.setAxis("aim_y", je::Controller::AxisBind(sf::Joystick::Axis::R));
	p1controls.setAxis("aim_x", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::X, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));
	p1controls.setAxis("aim_y", je::Controller::AxisBind(je::Controller::AxisBind::MouseAxis::Y, false, je::Controller::AxisBind::Interval(-128, 128), nullptr));


	addEntity(new Player(this, getWidth() / 2, getHeight() / 2, 0, p1config));


	//	set up background gradient
	bgVertices[0].color = bgVertices[1].color = sf::Color(11, 26, 34);
	bgVertices[2].color = bgVertices[3].color = sf::Color(31, 75, 95);
	bgVertices[0].position = sf::Vector2f(0, 0);
	bgVertices[1].position = sf::Vector2f(getWidth(), 0);
	bgVertices[2].position = sf::Vector2f(getWidth(), getHeight());
	bgVertices[3].position = sf::Vector2f(0, getHeight());
}

void Arena::drawGUI(sf::RenderTarget& target) const
{
}

void Arena::onUpdate()
{
}

void Arena::onDraw(sf::RenderTarget& target) const
{
}

void Arena::beforeDraw(sf::RenderTarget& target) const
{
	target.draw(bgVertices, 4, sf::Quads);
}

void Arena::loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes)
{
}

void Arena::createTiles(const std::string& filename, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh)
{
}

void Arena::transformTiles(const std::string& layerName, int tilesAcross, int tilesHigh, unsigned  **tiles)
{
}


}
