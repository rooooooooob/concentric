#include "Arena.hpp"

namespace con
{

Arena::Arena(je::Game *game)
	:je::Level(game, 640, 480)
{
}

void Arena::drawGUI(sf::RenderTarget& target) const
{

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