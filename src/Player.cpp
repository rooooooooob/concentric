#include "Player.hpp"

#include "Level.hpp"
#include "Game.hpp"
#include "Trig.hpp"
#include "Head.hpp"
#include <iostream>

const int RUNNING_ANIM_TIME = 11;

namespace con
{

Player::Player(je::Level *level, int x, int y, int team, const PlayerConfig& config, const je::Controller& controller)
	:je::Entity(level, "Player", sf::Vector2f(x, y), sf::Vector2i(16, 24), sf::Vector2i(-8, 0))
	,currentAnimation("running")
	,currentArmAnimation("sword")
	,input(controller)
	,gravity(0)
	,armAngle(0)
	,aimer(level->getGame().getTexManager().get("aimer.png"))
	,facing(Right)
{
	animations["running"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_running.png"), 24, 24, RUNNING_ANIM_TIME));
	animations["running"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos.x, pos.y);
		sprite.setOrigin(12, 0);
	});

	armAnimations["sword"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_katana.png"), 48, 32, RUNNING_ANIM_TIME));
	armAnimations["sword"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos);
		sprite.setOrigin(24, 10);
	});
	level->addEntity(new Head(level, pos.x, pos.y, *this));
	this->setDepth(-6);
}

Player::Facing Player::getFacing() const
{
	return facing;
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	auto it = animations.find(currentAnimation);
	if (it != animations.end())
		it->second->draw(target, states);
	auto it2 = armAnimations.find(currentArmAnimation);
	if (it2 != armAnimations.end())
		it2->second->draw(target, states);
	target.draw(aimer, states);
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
		facing = Left;
	}

	if (input.isActionHeld("move_right"))
	{
		pos.x += 2;
		currentAnimation = "running";
		animations[currentAnimation]->advanceFrame();
		facing = Right;
	}


	if (animations[currentAnimation])
	{
		animations[currentAnimation]->apply([&](sf::Sprite& sprite)
		{
			sprite.setPosition(pos.x, pos.y);
			sprite.setScale(facing, 1);
		});
	}
	armAngle = 0;

	armAnimations["sword"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos);
		sprite.setScale(1, facing);
	});
	aimer.setPosition(pos + je::lengthdir(64, armAngle));
}

}
