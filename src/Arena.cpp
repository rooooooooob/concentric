#include "Arena.hpp"
#include "Game.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Game.hpp"
#include "SolidGround.hpp"
#include "Scenery.hpp"
#include "Scoreboard.hpp"
#include "Controller.hpp"
#include "PlayerConfig.hpp"
#include "Player.hpp"

namespace con
{

Arena::Arena(je::Game *game, const Settings& settings)
	:je::Level(game, 640, 480)
	,settings(settings)
{
	scores.addTeam ();
	scores.addPlayer (0);
	scores.addTeam ();
	scores.addPlayer (1);

	for (int i = 0; i < getWidth(); i += 32)
	{
		for (int j = 1; j < 4; ++j)
			addEntity(new SolidGround(this, i, getHeight() - j * 32, sf::Rect<int>(i, getHeight() - j * 32, 32, 32), "dirt.png"));
		Scenery *grass = new Scenery(this, i, getHeight() - 3 * 32 - 6, (rand() % 2 ? "grass0.png" : "grass1.png"));
		grass->setDepth(-10);
		addEntity(grass);
	}

	int gapSize = getWidth() / (settings.getNumberOfPlayers() + 1);
	for (int i = 0; i < settings.getNumberOfPlayers(); ++i)
		addEntity(new Player(this, (i + 1) * gapSize, getHeight() / 2, settings.getPlayerConfig(i), scores));

	//	set up background gradient
	bgVertices[0].color = bgVertices[1].color = sf::Color(11, 26, 34);
	bgVertices[2].color = bgVertices[3].color = sf::Color(31, 75, 95);
	bgVertices[0].position = sf::Vector2f(0, 0);
	bgVertices[1].position = sf::Vector2f(getWidth(), 0);
	bgVertices[2].position = sf::Vector2f(getWidth(), getHeight());
	bgVertices[3].position = sf::Vector2f(0, getHeight());
	//	GAME JAM THEME: CASTLE
	Scenery *castle = new Scenery(this, getWidth() / 2 - (192/2), getHeight() - 3 * 32 -128, "castle.png");
	castle->setDepth(100.f);//in the distance (WHICH IS WHY IT'S SMALL!!!)
	this->addEntity(castle);
}

void Arena::drawGUI(sf::RenderTarget& target) const
{
	int n = scores.numberOfTeams();
	for (int i = 0; i < n; ++i)
	{
		std::stringstream ss;
		ss << "Team " << i + 1 << ":";
		int m = scores.numberOfPlayers(i);
		for (int j = 0; j < m; ++j)
		{
			ss << "\n	Player " << j + 1 << ": " << scores.getPlayerScore (i, j);
		}
		sf::Font f;
		if (!f.loadFromFile ("resources/arial.ttf"))
			std::cout << "bad font file";
		sf::Text t(ss.str(), f, 20);
		t.setColor (sf::Color::Blue);
		t.setPosition (150*i, 0);
		target.draw (t);
	}
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
