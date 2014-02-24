#include "Player/Attack.hpp"

#include "Player/Bone.hpp"

namespace con
{

Attack::Attack(je::Level *level, const Bone& bone, const PlayerConfig& config, int time, float damage)
	:je::Entity(level, "Attack", bone.getPos(), bone.getMask().getDetails().clone())
	,bone(bone)
	,config(config)
	,time(time)
	,damage(damage)
{
	transform() = bone.transform();
}


float Attack::getDamage() const
{
	return damage;
}

/*		private			*/
const PlayerConfig& Attack::getPlayerConfig() const
{
	return config;
}

void Attack::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

void Attack::onUpdate()
{
	if (--time < 0)
		this->destroy();
	transform() = bone.transform();
}



}
