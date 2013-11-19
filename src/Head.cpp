#include "Head.hpp"

#include "Game.hpp"
#include "Level.hpp"
#include "Random.hpp"
#include "Trig.hpp"
#include "ThrownWeapon.hpp"
#include "Blood.hpp"
#include "Scoreboard.hpp"
#include "PlayerResources.hpp"

namespace con
{

Head::Head(je::Level *level, int x, int y, Player& owner, Scoreboard& scores)
	:je::Entity(level, "Head", sf::Vector2f(x, y), sf::Vector2i(8, 8), sf::Vector2i(-4, -8))
	,owner(owner)
	,sprite(level->getGame().getTexManager().get(getClassPrefix(owner.getConfig().type) + "_head.png"))
	,health(50)
	,state(State::Capitated)
	,scores(scores)
{
	sprite.setOrigin(4, 4);
	sprite.setPosition(pos);
	this->setDepth(-5);
}

Head::State Head::getState() const
{
	return state;
}

void Head::damage(float amount)
{
	health -= amount;
	if (health <= 0)
	{
		state = State::Decapitated;
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
			std::vector<Entity*> thrownWeapons;
			level->findCollisions(thrownWeapons, this, "ThrownWeapon");
			for (je::Entity *entity : thrownWeapons)
			{
				ThrownWeapon& twep = *((ThrownWeapon*) entity);
				if (twep.getTeamID() != owner.getConfig().team)
				{
					this->damage(twep.getDamage() * 10);//	BOOM HEADSHOT
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
										 je::lengthdir(je::randomf(je::distance(twep.getVelocity()) + 2.f),
													   je::direction(twep.getVelocity()) - 9 + je::randomf(18)))
						);
					}
					twep.destroy();
				}
			}
			pos = owner.getPos();
		}
			break;
		case State::Decapitated:
			if (!level->testCollision(this, "SolidGround", velocity.x, velocity.y))
			{
				velocity.y += 0.06;
				pos += velocity;
				sprite.rotate(0.1);
			}
			if (pos.x < -32 || pos.x > level->getWidth() + 32)
				this->destroy();
			break;
	}

	sprite.setPosition(pos.x, pos.y - 4);
	sprite.setScale(owner.getFacing(), 1);
}

}
