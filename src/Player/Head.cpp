#include "Player/Head.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Player/Attack.hpp"
#include "Player/Blood.hpp"
#include "Player/PlayerResources.hpp"
#include "Player/ThrownWeapon.hpp"

#include "Scoreboard.hpp"


namespace con
{

Head::Head(je::Level *level, int x, int y, Player& owner, Scoreboard& scores)
	:je::Entity(level, "Head", sf::Vector2f(x, y), sf::Vector2i(8, 8), sf::Vector2i(-4, -8))
	,owner(owner)
	,sprite(level->getGame().getTexManager().get(getClassPrefix(owner.getConfig().type) + "_head.png"))
	,health(50)
	,state(State::Capitated)
	,scores(scores)
	,stuck(false)
{
	sprite.setOrigin(3, 4);
	sprite.setPosition(getPos());
	this->setDepth(-5);
}

Head::State Head::getState() const
{
	return state;
}

void Head::damage(float amount, const PlayerConfig *source)
{
	health -= amount;
	if (health <= 0 && state == State::Capitated)
	{
		state = State::Decapitated;
		scores.reportKill(*source, owner.getConfig());
	}
}

void Head::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite, states);
}

void Head::onUpdate()
{
	switch (state)
	{
		case State::Capitated:
		{
			std::vector<je::Ref<Entity>> collisionResults;
			level->findCollisions(collisionResults, this, "ThrownWeapon");
			for (je::Entity *entity : collisionResults)
			{
				ThrownWeapon& twep = *((ThrownWeapon*) entity);
				if (twep.getTeamID() != owner.getConfig().team)
				{
					this->damage(twep.getDamage() * 10, twep.getPlayerConfig());//	BOOM HEADSHOT
					owner.damage(twep.getDamage());
					if (health <= 0)
					{
						velocity = twep.getVelocity() / 2.f;
					}
					const int n = je::randomf(6) + 1;
					for (int i = 0; i < n; ++i)
					{
						level->addEntity(new Blood(level,
										 twep.getPos(),
										 je::lengthdir(je::randomf(je::length(twep.getVelocity()) + 2.f),
													   je::direction(twep.getVelocity()) - 9 + je::randomf(18)))
						);
					}
					twep.destroy();
				}
			}
			collisionResults.clear();
			level->findCollisions(collisionResults, this, "Attack");
			for (je::Entity *entity : collisionResults)
			{
				Attack& atk = *((Attack*) entity);
				if (atk.getPlayerConfig().team != owner.getConfig().team)
				{
					this->damage(atk.getDamage() * 2.f, &atk.getPlayerConfig());
					owner.damage(atk.getDamage() / 2.f);
					if (health <= 0)
					{
						//velocity = atk.getVelocity() / 2.f;
					}
					const int n = je::randomf(6) + 1;
					for (int i = 0; i < n; ++i)
					{
						level->addEntity(new Blood(level, atk.getPos(), je::lengthdir(9 - je::randomf(18), je::randomf(360.f))));
					}
					atk.destroy();
				}
			}
			transform().setPosition(owner.getPos());

			sprite.setScale(owner.getFacing(), 1);
		}
			break;
		case State::Decapitated:
			if (!stuck)
			{
				if (level->testCollision(this, "SolidGround", velocity.x, velocity.y))
				{
					stuck = true;
				}
				else
				{
					velocity.y += 0.06;
					transform().move(velocity);
					sprite.rotate(5);
				}
				if (getPos().x < -32 || getPos().x > level->getWidth() + 32)
					this->destroy();
			}
			break;
	}

	sprite.setPosition(getPos().x, getPos().y - 4);
}

}
