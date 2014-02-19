#ifndef CON_PLAYERCONFIG_HPP
#define CON_PLAYERCONFIG_HPP

#include "jam-engine/Core/Controller.hpp"

namespace con
{

struct PlayerConfig
{
	enum class Sword
	{
		Katana = 0,
		Spear
	};
	enum class Thrown
	{
		Shuriken = 0,
		Knife
	};
	enum class Type
	{
		Samurai = 0,
		Ninja
	};
	PlayerConfig(Sword sword, Thrown thrown, Type type, int team, const je::Controller& controller, int playerID)
		:sword(sword)
		,thrown(thrown)
		,type(type)
		,team(team)
		,controller(controller)
		,playerID(playerID)
	{
	}


	Sword sword;
	Thrown thrown;
	Type type;
	int team;
	int playerID;
	je::Controller controller;
};

}

#endif
