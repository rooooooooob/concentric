#ifndef CON_ATTACK_HPP
#define CON_ATTACK_HPP

#include "jam-engine/Core/Entity.hpp"
#include "Player/PlayerConfig.hpp"

namespace con
{

class Bone;

class Attack : public je::Entity
{
public:
	Attack(je::Level *level, const Bone& bone, const PlayerConfig& config, int time, float damage);


	float getDamage() const;

	const PlayerConfig& getPlayerConfig() const;

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;


	const Bone& bone;
	const PlayerConfig& config;
	int time;
	float damage;

};

}

#endif
