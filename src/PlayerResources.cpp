#include "PlayerResources.hpp"

namespace con
{

std::string getThrowingArmSprite(PlayerConfig::Thrown thrown)
{
	switch (thrown)
	{
		case PlayerConfig::Thrown::Shuriken:
			return "shuriken.png";
		case PlayerConfig::Thrown::Knife:
			return "knife.png";
	}
	return "default_thrown";
}

std::string getSwingingArmSprite(PlayerConfig::Sword sword)
{
	switch (sword)
	{
		case PlayerConfig::Sword::Katana:
			return "katana.png";
		case PlayerConfig::Sword::Spear:
			return "spear.png";
	}
	return "default_sword";
}

std::string getClassPrefix(PlayerConfig::Type type)
{
	switch (type)
	{
		case PlayerConfig::Type::Ninja:
			return "ninja";
		case PlayerConfig::Type::Samurai:
			return "samurai";
	}
	return "default_class";
}

}