#ifndef CON_PLAYERRESOURCES_HPP
#define CON_PLAYERRESOURCES_HPP

#include "PlayerConfig.hpp"

namespace con
{

extern std::string getThrowingArmSprite(PlayerConfig::Thrown thrown);

extern std::string getSwingingArmSprite(PlayerConfig::Sword sword);

extern std::string getClassPrefix(PlayerConfig::Type type);

}

#endif