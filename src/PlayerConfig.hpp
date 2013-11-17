#ifndef CON_PLAYERCONFIG_HPP
#define CON_PLAYERCONFIG_HPP

#include "Controller.hpp"

namespace con
{

struct PlayerConfig
{
	enum class Sword
	{
		Katana,
		Spear
	};
	enum class Thrown
	{
		Shuriken,
		Knife
	};
	enum class Type
	{
		Samurai,
		Ninja
	};
	PlayerConfig(Sword sword, Thrown thrown, Type type, int team, const je::Controller& controller)
		:sword(sword)
		,thrown(thrown)
		,type(type)
		,team(team)
		,controller(controller)
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
