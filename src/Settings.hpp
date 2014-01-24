#ifndef CON_SETTINGS_HPP
#define CON_SETTINGS_HPP

#include <vector>
#include "Core/Game.hpp"
#include "Core/Controller.hpp"

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

	void removePlayer();

	int getNumberOfPlayers() const;

private:
	void defaultControlsX360(je::Controller& input);

	void defaultControlsPS3(je::Controller& input);

	void defaultControlsPC(je::Controller& input);


	std::vector<PlayerConfig> configs;
	je::Game& game;
};

}

#endif
