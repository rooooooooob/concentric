#ifndef CON_ARENA_HPP
#define CON_ARNEA_HPP

#include "Level.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "Controller.hpp"
#include "Settings.hpp"

namespace con
{

class Arena : public je::Level
{
public:
	Arena(je::Game *game, const Settings& settings);

	void drawGUI(sf::RenderTarget& target) const override;

private:
	void onUpdate() override;

	void onDraw(sf::RenderTarget& target) const override;

	void beforeDraw(sf::RenderTarget& target) const override;

	void loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes) override;

	void createTiles(const std::string& filename, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh) override;

	void transformTiles(const std::string& layerName, int tilesAcross, int tilesHigh, unsigned  **tiles) override;




	sf::Vertex bgVertices[4];
	const Settings& settings;
};

}

#endif // CON_ARENA_HPP
