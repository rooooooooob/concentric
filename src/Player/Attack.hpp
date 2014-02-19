#ifndef CON_ATTACK_HPP
#define CON_ATTACK_HPP

#include "jam-engine/Core/Entity.hpp"
#include "Player/PlayerConfig.hpp"

namespace con
{

class Attack : public je::Entity
{
public:
	Attack(je::Level *level, const sf::Vector2f *follow, const sf::Vector2f& cpos, const sf::Vector2i& dim, const PlayerConfig& config, int time, float damage, const sf::Vector2f& veloc = sf::Vector2f(0, 0));

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
	void onUpdate() override;

	float getDamage() const;
	const PlayerConfig& getPlayerConfig() const;

protected:
	const sf::Vector2f *follow;
	sf::Vector2f cpos;
	sf::Vector2f veloc;

private:
	const PlayerConfig& config;
	int time;
	float damage;
};

}

#endif
