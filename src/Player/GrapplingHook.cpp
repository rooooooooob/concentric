#include "Player/GrapplingHook.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/CollisionMaskManager.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Player/Player.hpp"
#include "Player/PlayerConfig.hpp"

namespace con
{

GrapplingHook::GrapplingHook(Player& player, const sf::Vector2f& pos, const sf::Vector2f& velocity)
	:je::Entity(player.getLevel(), "GrapplingHook", pos, sf::Vector2i(4, 4), sf::Vector2i(-3, -2))
	,player(player)
	,velocity(velocity)
	,gravity(0.17f)
	,stuck(false)
{
	je::TexManager& texMan = level->getGame().getTexManager();
	hookSprite.setTexture(texMan.get("hook.png"));
	hookSprite.setOrigin(4, 2);
	hookSprite.setPosition(pos);

	line[0].color = line[1].color = sf::Color(139, 119, 92);
}

bool GrapplingHook::pullIn()
{
	if (stuck)
	{
		bool hit;
		player.veloc = level->rayCastManually(hit, &player, {"SolidGround"},[](const je::Entity&)->bool{return true;}, je::lengthdir(5, je::pointDirection(player.getPos(), getPos()))) - player.getPos();
		//player.transform().setPosition();
	}
	else
	{
		velocity = je::lengthdir(9, je::pointDirection(getPos(), player.getPos()));
	}
	return (je::pointDistance(getPos(),  player.getPos()) <= je::length(velocity));
}

// private
void GrapplingHook::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(line, 2, sf::PrimitiveType::Lines, states);
	target.draw(hookSprite, states);
}

void GrapplingHook::onUpdate()
{
	if (!stuck)
	{
		transform().setRotation(-je::direction(velocity));
		hookSprite.setRotation(-je::direction(velocity));
		gravity += 0.003f;
		
		bool hit = false;
		const sf::Vector2f newPos(level->rayCastManually(hit, this, {"ThrownWeapon", "Attack"}, [](const Entity& e) {
			return true; // for now, at least. change if your own attacks don't block shurikens
		}, velocity));
		if (hit)
		{
			velocity = je::lengthdir(je::randomf(7.f), 50.f + je::randomf(80.f));
		}
		transform().setPosition(newPos);

		hookSprite.setPosition(getPos());
		velocity.y += 0.17;
	
	
		if (getPos().x < 0 || getPos().x > level->getWidth() || getPos().y < 0 || getPos().y > level->getHeight())
			stuck = true;//this->destroy();
		if (level->testCollision(this, "SolidGround"))
			stuck = true;
	}
	line[0].position = player.getPos();
	line[1].position = getPos();
}

} // con
