#ifndef CON_POWERUP_HPP
#define CON_POWERUP_HPP

#include "jam-engine/Core/Entity.hpp"

namespace con
{

class Powerup : public je::Entity
{
public:
	enum class Type
	{
		ThreeShot,
		Health,
		BigWeapon
	};
	Powerup(je::Level *level, const sf::Vector2f& pos, Type type);

	Type getType() const;


private:
	void onUpdate() override;
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;



	sf::Sprite sprite;
	sf::Vector2f veloc;
	int timer;
	bool isStuck;
	Type type;
};

}

#endif