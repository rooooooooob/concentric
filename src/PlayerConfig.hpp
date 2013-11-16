#ifndef CON_PLAYERCONFIG_HPP
#define CON_PLAYERCONFIG_HPP

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


	Sword sword;
	Thrown thrown;
	Type type;
};

}

#endif