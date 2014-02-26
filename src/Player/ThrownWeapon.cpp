#include "Player/ThrownWeapon.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/CollisionMaskManager.hpp"
#include "jam-engine/Physics/PolygonMask.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace con
{

static je::DetailedMask::MaskRef getThrownMask(PlayerConfig::Thrown type, je::Level *level)
{
	static bool loaded = false;
	if (!loaded)
	{
		je::CollisionMaskManager& db = level->getGame().masks();
		je::DetailedMask::MaskRef mask(new je::PolygonMask(8, 3));
		db.add("Knife", mask);
		mask.reset(new je::PolygonMask(4, 4));
		db.add("Shuriken", mask);
		loaded = true;
	}
	switch (type)
	{
		case PlayerConfig::Thrown::Knife:
			return level->getGame().masks().create("Knife");
		case PlayerConfig::Thrown::Shuriken:
			return level->getGame().masks().create("Shuriken");
	}
}


ThrownWeapon::ThrownWeapon(je::Level *level, const sf::Vector2f& pos, const PlayerConfig& config, const sf::Vector2f& velocity)
	:je::Entity(level, "ThrownWeapon", pos, getThrownMask(config.thrown, level))
	,sprite()
	,config(config)
	,velocity(velocity)
	,gravity(0)
	,damage(0)
	,wasBlocked(false)

{
	je::TexManager& texMan = level->getGame().getTexManager();
	switch (config.thrown)
	{
		case PlayerConfig::Thrown::Shuriken:
			sprite.setTexture(texMan.get("shuriken.png"));
			sprite.setOrigin(4, 4);
			gravity = 0.3;
			damage = 15;
			break;
		case PlayerConfig::Thrown::Knife:
			sprite.setTexture(texMan.get("knife.png"));
			sprite.setOrigin(3, 2);
			gravity = 0.1;
			damage = 12;
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

const PlayerConfig* ThrownWeapon::getPlayerConfig ()
{
	return &config;
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
			sprite.rotate(je::length(velocity) * 2);
			break;
		case PlayerConfig::Thrown::Knife:
			transform().setRotation(-je::direction(velocity));
			sprite.setRotation(-je::direction(velocity));
			gravity += 0.01;
			break;
	}

	if (!wasBlocked)
	{
		bool hit = false;
		const sf::Vector2f newPos(level->rayCastManually(hit, this, {"ThrownWeapon", "Attack"}, [](const Entity* e) {
			return true; // for now, at least. change if your own attacks don't block shurikens
		}, velocity));
		if (hit)
		{
			velocity = je::lengthdir(je::randomf(7.f), 50.f + je::randomf(80.f));
			wasBlocked = true;
		}
		transform().setPosition(newPos);
	}
	else
	{
		transform().move(velocity);
	}
	sprite.setPosition(getPos());
	velocity.y += gravity;
	
	
	if (getPos().x < 0 || getPos().x > level->getWidth() || getPos().y < 0 || getPos().y > level->getHeight())
		this->destroy();
	if (level->testCollision(this, "SolidGround"))
		this->destroy();
}

}
