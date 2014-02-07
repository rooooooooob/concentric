#ifndef CON_THROWNWEAPON_HPP
#define CON_THROWNWEAPON_HPP

#include "jam-engine/Core/Entity.hpp"
#include "PlayerConfig.hpp"

namespace con
{

class ThrownWeapon : public je::Entity
{
public:
	ThrownWeapon(je::Level *level, const sf::Vector2f& pos, const PlayerConfig& config, const sf::Vector2f& velocity);

	const sf::Vector2f& getVelocity() const;

	float getDamage() const;

	int getPlayerID() const;

	int getTeamID() const;

	const PlayerConfig* getPlayerConfig ();

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;


	sf::Sprite sprite;
	const PlayerConfig& config;
	sf::Vector2f velocity;
	float gravity;
	float damage;
};

}

#endif // CON_THROWNWEAPON_HPP
