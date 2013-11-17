#include "ThrownWeapon.hpp"

#include "Game.hpp"
#include "Level.hpp"
#include "Trig.hpp"

namespace con
{

ThrownWeapon::ThrownWeapon(je::Level *level, const sf::Vector2f& pos, const PlayerConfig& config, const sf::Vector2f& velocity)
	:je::Entity(level, "ThrownWeapon", pos, sf::Vector2i(7, 7), sf::Vector2i(-3, -3))
	,sprite()
	,config(config)
	,velocity(velocity)
	,gravity(0)
	,damage(0)

{
	je::TexManager& texMan = level->getGame().getTexManager();
	switch (config.thrown)
	{
		case PlayerConfig::Thrown::Shuriken:
			sprite.setTexture(texMan.get("shuriken.png"));
			sprite.setOrigin(4, 4);
			gravity = 0.3;
			damage = 10;
			break;
		case PlayerConfig::Thrown::Knife:
			sprite.setTexture(texMan.get("knife.png"));
			sprite.setOrigin(3, 2);
			gravity = 0.1;
			damage = 10;
			break;
	}
	sprite.setPosition(pos);
}

const sf::Vector2f& ThrownWeapon::getVelocity() const
{
	return velocity;
}

float ThrownWeapon::getDamage() const
{
	return damage;
}

int ThrownWeapon::getPlayerID() const
{
	return config.team;
}

int ThrownWeapon::getTeamID() const
{
	return config.team;//update this later
}


void ThrownWeapon::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite, states);
}

void ThrownWeapon::onUpdate()
{
	switch (config.thrown)
	{
		case PlayerConfig::Thrown::Shuriken:
			sprite.rotate(je::distance(velocity) * 2);
			break;
		case PlayerConfig::Thrown::Knife:
			sprite.setRotation(-je::direction(velocity));
			gravity += 0.01;
			break;
	}
	sprite.setPosition(pos);
	velocity.y += gravity;
	pos += velocity;

	if (pos.x < 0 || pos.x > level->getWidth() || pos.y < 0 || pos.y > level->getHeight())
		this->destroy();
	if (level->testCollision(this, "SolidGround"))
		this->destroy();
}

}
