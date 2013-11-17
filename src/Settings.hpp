#ifndef CON_SETTINGS_HPP
#define CON_SETTINGS_HPP

#include <vector>
#include "Game.hpp"
#include "Controller.hpp"
#include "PlayerConfig.hpp"

namespace con
{

class Settings
{
public:
	Settings(je::Game& game);

	PlayerConfig& getPlayerConfig(int playerIndex);

	const PlayerConfig& getPlayerConfig(int playerIndex) const;

	void addPlayer();

	int getNumberOfPlayers() const;

private:
	std::vector<PlayerConfig> configs;
	je::Game& game;
};

}

#endif
