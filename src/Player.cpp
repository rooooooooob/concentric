#include "Player.hpp"

#include "Level.hpp"
#include "Game.hpp"
#include <iostream>

const int RUNNING_ANIM_TIME = 11;

namespace con
{

Player::Player(je::Level *level, int x, int y, int team, const PlayerConfig& config, const je::Controller& controller)
	:je::Entity(level, "Player", sf::Vector2f(x, y), sf::Vector2i(16, 24), sf::Vector2i(-8, 0))
	,currentAnimation("running")
	,input(controller)
	,gravity(0)
{
	animations["running"].reset(new je::Animation(level->getGame().getTexManager().get("running_blue.png"), 24, 24, RUNNING_ANIM_TIME));
	animations["running"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos.x, pos.y);
		sprite.setOrigin(12, 0);
	});
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	auto it = animations.find(currentAnimation);
	if (it != animations.end())
		it->second->draw(target, states);
}

void Player::onUpdate()
{
	if (level->testCollision(this, "SolidGround", 0, gravity))
	{
		gravity = 0;
		if (input.isActionPressed("jump"))
			gravity = -5;
	}
	else
	{
		gravity += 0.3;
		pos.y += gravity;
	}

	if (input.isActionHeld("move_left"))
	{
		pos.x -= 2;
		currentAnimation = "running";
		animations[currentAnimation]->advanceFrame();
		animations[currentAnimation]->apply([&](sf::Sprite& sprite)
		{
			sprite.setScale(-1, 1);
		});
	}

	if (input.isActionHeld("move_right"))
	{
		pos.x += 2;
		currentAnimation = "running";
		animations[currentAnimation]->advanceFrame();
		animations[currentAnimation]->apply([&](sf::Sprite& sprite)
		{
			sprite.setScale(1, 1);
		});
	}


	if (animations[currentAnimation])
	{
		animations[currentAnimation]->apply([&](sf::Sprite& sprite)
		{
			sprite.setPosition(pos.x, pos.y);
		});
	}
}

}