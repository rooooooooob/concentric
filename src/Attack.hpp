#ifndef CON_ATTACK_HPP
#define CON_ATTACK_HPP

#include "Entity.hpp"

namespace con
{

class Attack : public je::Entity
{
public:
	Attack(je::Level *level, const sf::Vector2f *follow, const sf::Vector2f& cpos, const sf::Vector2i& dim, int team, int time, float damage, const sf::Vector2f& veloc = sf::Vector2f(0, 0));

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
	void onUpdate() override;

	float getDamage() const;
	int getTeam() const;

protected:
	const sf::Vector2f *follow;
	sf::Vector2f cpos;
	sf::Vector2f veloc;

private:
	int team;
	int time;
	float damage;
};

}

#endif
