#include "Arena.hpp"
#include "Core/Game.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Core/Game.hpp"
#include "SolidGround.hpp"
#include "Scenery.hpp"
#include "Scoreboard.hpp"
#include "Core/Controller.hpp"
#include "PlayerConfig.hpp"
#include "Player.hpp"
#include "BambooForest.hpp"
#include "Utility/Random.hpp"

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
	const int groundHeight = getHeight() - 128;
	int yoffset = 0;
	for (int i = 0; i < getWidth(); i += 32)
	{
		yoffset += je::random(8) - 4;
		if (yoffset > 8)
			yoffset = 8;
		if (yoffset < -12)
			yoffset = -12;
		for (int j = groundHeight + yoffset; j < getHeight(); j += 32)
		{
			SolidGround *ground = new SolidGround(this, i, j, sf::Rect<int>(i, j, 32, 32), "dirt.png");
			ground->setDepth(-10);
			this->addEntity(ground);
		}
		Scenery *grass = new Scenery(this, i, groundHeight - 6 + yoffset, (rand() % 2 ? "grass0.png" : "grass1.png"));
		grass->setDepth(-11);
		this->addEntity(grass);
	}

	Scenery *beam = new Scenery(this, 32 + 16, groundHeight - 32, "beam.png");
	beam->setDepth(1);
	this->addEntity(beam);
	beam = new Scenery(this, 164 + 16 + 4, groundHeight - 32, "beam.png");
	beam->setDepth(1);
	addEntity(beam);
	for (int i = 32; i < 164; i += 32)
	{
		addEntity(new SolidGround(this, i, groundHeight - 32, sf::Rect<int>(i, groundHeight - 32, 32, 6), "platform.png"));
	}

	int gapSize = getWidth() / (settings.getNumberOfPlayers() + 1);
	for (int i = 0; i < settings.getNumberOfPlayers(); ++i)
		this->addEntity(new Player(this, (i + 1) * gapSize, getHeight() / 2, settings.getPlayerConfig(i), scores));

	//	set up background gradient
	bgVertices[0].color = bgVertices[1].color = sf::Color(11, 26, 34);
	bgVertices[2].color = bgVertices[3].color = sf::Color(40, 90, 116);
	bgVertices[0].position = sf::Vector2f(0, 0);
	bgVertices[1].position = sf::Vector2f(getWidth(), 0);
	bgVertices[2].position = sf::Vector2f(getWidth(), getHeight());
	bgVertices[3].position = sf::Vector2f(0, getHeight());
	//	GAME JAM THEME: CASTLE
	Scenery *castle = new Scenery(this, getWidth() / 2 - (192/2), groundHeight -128, "castle.png");
	castle->setDepth(100);//in the distance (WHICH IS WHY IT'S SMALL!!!)
	this->addEntity(castle);

	//	forest time!
	const float totalDensity = 0.85f;
	const float sideDensity = totalDensity / 4.f;
	const float backDensity = totalDensity - sideDensity;
	const int frontForestWidth = 164;
	//	add background forest
	addEntity(new BambooForest(this, sf::Vector2f(0, groundHeight), this->getWidth(), totalDensity));
	//	and one to make up for the frontal side forests (to keep uniform tree density across map)
	addEntity(new BambooForest(this, sf::Vector2f(frontForestWidth, groundHeight), this->getWidth() - frontForestWidth * 2, sideDensity));

	//	and the two frontal forests
	BambooForest *frontForest = new BambooForest(this, sf::Vector2f(0, groundHeight), frontForestWidth, sideDensity);
	frontForest->setDepth(-9);	//	behind grass and land, in front of rest
	this->addEntity(frontForest);
	frontForest = new BambooForest(this, sf::Vector2f(getWidth() - frontForestWidth, groundHeight), frontForestWidth, sideDensity);
	frontForest->setDepth(-9);	//	behind grass and land, in front of rest
	this->addEntity(frontForest);

	//	init all score text crap (jesus christ max why would you recreate this every frame?)
	if (!font.loadFromFile ("resources/DOMOAN__.ttf"))
		std::cerr << "bad font file";
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setColor (sf::Color::White);

	//	make sure heads are updated after players! (or else the heads lag behind)
	this->setSpecificOrderEntitiesPost({"Head"});
}

void Arena::drawGUI(sf::RenderTarget& target) const
{
	int n = scores.numberOfTeams();
	for (int i = 0; i < n; ++i)
	{
		std::stringstream ss;
		ss << "Team " << i + 1;
		int m = scores.numberOfPlayers(i);
		for (int j = 0; j < m; ++j)
		{
			ss << "\n	Player " << j + 1 << ": " << scores.getPlayerScore (i, j);
		}
		scoreText.setString(ss.str());
		const int gapSpaceLeft = getWidth() - n * scoreText.getLocalBounds().width - 16;
		scoreText.setPosition((gapSpaceLeft / (n - 1)) * i + scoreText.getLocalBounds().width / 2, 8);

		target.draw(scoreText);
	}
}

void Arena::onUpdate()
{
	std::stringstream ss;
	ss << "";
	if (getGame().getFPS() < getGame().getFPSCap() * 0.95)
	{
		ss << "\t\tFPS: " << getGame().getFPS() << "[" << getGame().getExactFPS() << "] / " << getGame().getFPSCap();
	}
	getGame().setTitle(ss.str());
}

void Arena::onDraw(sf::RenderTarget& target) const
{
}

void Arena::beforeDraw(sf::RenderTarget& target) const
{
	//	draw the gradient sky background
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
