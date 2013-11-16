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
	this->setCameraBounds(sf::Rect<int>(0, 0, getWidth(), getHeight()));
	this->setCameraPosition(sf::Vector2f(getWidth() / 2, getHeight() / 2));
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
		PlayerConfig::Type::Ninja
	};

	je::Controller p1controls(getGame().getInput(), 0);
	p1controls.addKeybind("jump", je::Controller::Bind(4));
	p1controls.addKeybind("jump", je::Controller::Bind(sf::Joystick::Axis::Y, true));
	p1controls.addKeybind("move_right", je::Controller::Bind(sf::Joystick::Axis::X));
	p1controls.addKeybind("move_left", je::Controller::Bind(sf::Joystick::Axis::X, true));

	addEntity(new Player(this, getWidth() / 2, getHeight() / 2, 0, p1config, p1controls));


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
