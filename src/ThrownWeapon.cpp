#include "ThrownWeapon.hpp"

#include "Game.hpp"
#include "Level.hpp"

namespace con
{

ThrownWeapon::ThrownWeapon(je::Level *level, const sf::Vector2f& pos, const PlayerConfig& config, const sf::Vector2f& velocity)
	:je::Entity(level, "ThrownWeapon", pos, sf::Vector2i(7, 7))
	,sprite()
	,config(config)
{
	je::TexManager& texMan = level->getGame().getTexManager();
	switch (config.thrown)
	{
		case PlayerConfig::Thrown::Shuriken:
			sprite.setTexture(texMan.get("shuriken.png"));
			sprite.setOrigin(4, 4);
			gravity = 0.3;
			break;
		case PlayerConfig::Thrown::Knife:
			sprite.setTexture(texMan.get("knife.png"));
			sprite.setOrigin(3, 2);
			gravity = 0.1;
			break;
	}
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
			break;
		case PlayerConfig::Thrown::Knife:
			gravity += 0.001;
			break;
	}
	velocity.y += gravity;
	pos += velocity;

	if (pos.x < 0 || pos.x < level->getWidth() || pos.y < 0 || pos.y > level->getHeight())
		this->destroy();
	if (level->testCollision(this, "SolidGround"))
		this->destroy();
}

}
