#include "Level/Powerup.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

namespace con
{

Powerup::Powerup(je::Level *level, const sf::Vector2f& pos, Type type)
	:je::Entity(level, "Powerup", pos, sf::Vector2i(8, 8), sf::Vector2i(-4, 0))
	,veloc(0, 0)
	,timer(360)
	,isStuck(false)
	,type(type)
{
	switch (type)
	{
	case Type::ThreeShot:
		sprite.setTexture(level->getGame().getTexManager().get("3shotpickup.png"));
		break;
	case Type::Health:
		sprite.setTexture(level->getGame().getTexManager().get("healthpickup.png"));
		break;
	case Type::BigWeapon:
		sprite.setTexture(level->getGame().getTexManager().get("meleepickup.png"));
		break;
	}
	sprite.setOrigin(4, 4);
	sprite.setPosition(pos);
	this->setDepth(-10000);
}

Powerup::Type Powerup::getType() const
{
	return type;
}

void Powerup::onUpdate()
{
	if (--timer < 0)
		this->destroy();
	if (!isStuck)
	{
		if (level->testCollision(this, "SolidGround", 0, 3))
		{
			isStuck = true;
		}
		else
		{
			veloc.y += 0.2;
			if (veloc.y > 10)
				veloc.y = 10;
			transform().move(veloc);

			if (getPos().x < -16 || getPos().x > level->getWidth() + 16)
				this->destroy();

			sprite.setPosition(getPos());
		}
	}
}

void Powerup::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	if (timer < 90)
	{
		if ((timer / 10) % 2 == 0)
			return;
	}
	target.draw(sprite, states);
}

}
