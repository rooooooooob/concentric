#ifndef CON_ARENA_HPP
#define CON_ARENA_HPP

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Input.hpp"
#include "UI/Window.hpp"
#include "jam-engine/Core/Controller.hpp"
#include "Settings.hpp"
#include "Scoreboard.hpp"

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

	void updateScores();


	sf::Vertex bgVertices[4];
	const Settings& settings;
	Scoreboard scores;
	sf::Font font;
	std::vector<sf::Text> scoreTexts;
};

}

#endif // CON_ARENA_HPP
