#include "Arena.hpp"
#include "Game.hpp"

namespace con
{

Arena::Arena(je::Game *game)
	:je::Level(game, 640, 480),
	w(sf::Vector2f (0, 0), sf::Vector2f (300, 300), this),
	controller (this->getGame().getInput())
{
   w.buttons.push_back (Button (sf::Vector2f (100, 100), sf::Vector2f (50, 50), "test1", this));
   w.buttons.push_back (Button (sf::Vector2f (200, 200), sf::Vector2f (50, 50), "test2", this));
   w.buttons.push_back (Button (sf::Vector2f (200, 100), sf::Vector2f (50, 50), "test3", this));
   w.buttons.push_back (Button (sf::Vector2f (25, 40), sf::Vector2f (50, 50), "test4", this));
}

void Arena::drawGUI(sf::RenderTarget& target) const
{
    w.draw (target);
}

void Arena::onUpdate()
{

}

void Arena::onDraw() const
{
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
