#ifndef CON_ARENA_HPP
#define CON_ARNEA_HPP

#include "Level.hpp"

namespace con
{

class Arena : public je::Level
{
public:
	Arena(je::Game * game);

	void drawGUI(sf::RenderTarget& target) const;

private:
	void onUpdate();

	void onDraw() const;

	void loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes);

	void createTiles(const std::string& filename, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh);

	void transformTiles(const std::string& layerName, int tilesAcross, int tilesHigh, unsigned  **tiles);

};

}

#endif // CON_ARENA_HPP
