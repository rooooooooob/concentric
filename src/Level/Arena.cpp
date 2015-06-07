#include "Level/Arena.hpp"

#include <iostream>

#include <cstdlib>
#include <functional>
#include <sstream>

#include "jam-engine/Core/Controller.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Level/BambooForest.hpp"
#include "Level/JumpThroughPlatform.hpp"
#include "Level/Powerup.hpp"
#include "Level/Scenery.hpp"
#include "Level/SolidGround.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerConfig.hpp"
#include "Scoreboard.hpp"


//#include "PolyTest.hpp"
//#include <memory>
//#include "jam-engine/Physics/DetailedMask.hpp"
//#include "jam-engine/Physics/PolygonMask.hpp"

namespace con
{

Arena::Arena(je::Game *game, const Settings& settings)
	:je::Level(game, 640, 480)
	,settings(settings)
	,scores(std::bind(&Arena::updateScores, this))
{
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
		addEntity(new JumpThroughPlatform(this, sf::Vector2f(i, groundHeight - 32)));
	}
	addEntity(new JumpThroughPlatform(this, sf::Vector2f(0, groundHeight - 88)));
	addEntity(new JumpThroughPlatform(this, sf::Vector2f(32, groundHeight - 88)));
	for (int i = 128; i < 256; i += 32)
	{
		addEntity(new JumpThroughPlatform(this, sf::Vector2f(i - 16, groundHeight - 128)));
	}

	int gapSize = getWidth() / (settings.getNumberOfPlayers() + 1);
	for (int i = 0; i < settings.getNumberOfPlayers(); ++i)
	{
		Player *player = new Player(this, (i + 1) * gapSize, getHeight() / 2, settings.getPlayerConfig(i), scores);
		scores.registerPlayer(player->getConfig());
		this->addEntity(player);
	}

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
	const bool netbook = true;
	if (netbook)
	{
		Scenery *forest = new Scenery(this, 0, 116, "bamboo_nolag.png");
		forest->setDepth(9001);
		addEntity(forest);

	}
	else
	{
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
	}

	//	init all score text crap (jesus christ max why would you recreate this every frame?)
	if (!font.loadFromFile ("resources/DOMOAN__.ttf"))
		std::cerr << "bad font file";
	scoreTexts.resize(settings.getNumberOfPlayers(), sf::Text()); 
	for (sf::Text& scoreText : scoreTexts)
	{
		scoreText.setFont(font);
		scoreText.setCharacterSize(20);
		scoreText.setColor(sf::Color::White);
	}

	//	make sure players are updated before heads and bones (or else the heads lag behind)
	this->setSpecificOrderEntitiesPre({"Player"});



	this->updateScores();

	//for (int i = 0; i < 1; ++i)
	//{
	//	addEntity(new PolyTest(
	//		this,
	//		sf::Vector2f(200, 100),
	//		std::unique_ptr<je::DetailedMask>(
	//			new je::PolygonMask({
	//					sf::Vector2f(-32, 24),
	//					sf::Vector2f(32, 24),
	//					sf::Vector2f(0, -24)
	//				})
	//		)
	//	));
	//}
}

void Arena::drawGUI(sf::RenderTarget& target) const
{
	for (const sf::Text& scoreText : scoreTexts)
		target.draw(scoreText);
}

void Arena::onUpdate()
{
	if (je::random(400) == 9)
	{
		Powerup::Type type = je::choose({Powerup::Type::Health, Powerup::Type::BigWeapon, Powerup::Type::ThreeShot});
		addEntity(new Powerup(this, sf::Vector2f(32 + je::random(getWidth() - 64), 32), type));
	}
#ifdef JE_DEBUG
	const bool ctrlHeld = getGame().getInput().isKeyHeld(sf::Keyboard::LControl);
	if (ctrlHeld && getGame().getInput().isKeyPressed(sf::Keyboard::F9))
		getGame().setDebugCollisionDrawDetails(!getGame().getDebugCollisionDrawDetails());
	if (ctrlHeld && getGame().getInput().isKeyPressed(sf::Keyboard::F10))
		getGame().setDebugCollisionDrawAABB(!getGame().getDebugCollisionDrawAABB());
#endif
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


void Arena::updateScores()
{
	const Scoreboard::TeamMap& teamIDs = scores.getTeamMap();
	const int n = teamIDs.size();

	int i = 0;
	for (const auto& playerIDs : teamIDs)
	{
		std::stringstream ss;
		ss << "Team " << playerIDs.first << " - " << scores.calculateTeamScore(playerIDs.first).score();
		for (Scoreboard::PlayerID playerID : playerIDs.second)
		{
			const Scoreboard::Score& score = scores.getPlayerScore(playerID);
			ss << "\n	Player " << playerID << ": " << score.score();// << " ( " << score.kills << "/ " << score.deaths << " / " << score.suicides << ")";
		}
		scoreTexts[i].setString(ss.str());
		const int gapSpaceLeft = getWidth() - n * scoreTexts[i].getLocalBounds().width - 16;
		scoreTexts[i].setPosition((gapSpaceLeft / (n - 1)) * i + scoreTexts[i].getLocalBounds().width / 2, 8);

		++i;
	}
}



}
