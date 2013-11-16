#include "Arena.hpp"

#include <cstdlib>
#include "Game.hpp"
#include "SolidGround.hpp"
#include "Scenery.hpp"

namespace con
{

Arena::Arena(je::Game *game)
	:je::Level(game, 640, 480)
{
	for (int i = 0; i < 640; i += 32)
    {
        for (int j = 1; j < 4; ++j)
            addEntity(new SolidGround(this, i, 480 - j * 32, sf::Rect<int>(i, 480 - j * 32, 32, 32), "dirt.png"));
        Scenery *grass = new Scenery(this, i, 480 - 3 * 32 - 6, (rand() % 2 ? "grass0.png" : "grass1.png"));
        grass->setDepth(-10);
        addEntity(grass);
    }
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
