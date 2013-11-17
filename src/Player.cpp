#include "Player.hpp"

#include "Level.hpp"
#include "Game.hpp"
#include "Trig.hpp"
#include "Head.hpp"
#include "ThrownWeapon.hpp"
#include <iostream>
const int RUNNING_ANIM_TIME = 11;

namespace con
{

Player::Player(je::Level *level, int x, int y, const PlayerConfig& config, Scoreboard& scores)
	:je::Entity(level, "Player", sf::Vector2f(x, y), sf::Vector2i(16, 24), sf::Vector2i(-8, 0))
	,currentAnimation("running")
	,currentArmAnimation("sword")
	,config(config)
	,input(config.controller)
	,gravity(0)
	,armAngle(0)
	,aimer(level->getGame().getTexManager().get("aimer.png"))
	,aim(0, 0)
	,facing(Right)
	,state(State::Idle)
	,cooldown(0)
	,scores (scores)
{
	animations["running"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_running.png"), 24, 24, RUNNING_ANIM_TIME));
	animations["running"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos);
		sprite.setOrigin(12, 0);
	});
	animations["jumping"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_jumping.png"), 24, 24, 0));
	animations["jumping"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos);
		sprite.setOrigin(12, 0);
	});

	armAnimations["melee"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_katana.png"), 48, 32, 12, false));
	armAnimations["melee"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos);
		sprite.setOrigin(24, 10);
	});
	armAnimations["throw"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_shuriken.png"), 48, 32, 4, false));
	armAnimations["throw"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos);
		sprite.setOrigin(24, 10);
	});

	level->addEntity(new Head(level, pos.x, pos.y, *this));
	this->setDepth(-6);

	currentArmAnimation = "melee";
	std::cout << "cooldown: " << &cooldown << " \n   ";
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
	aim.x = input.axisPos("aim_x", pos.x, level);
	aim.y = input.axisPos("aim_y", pos.y, level);

	const bool onGround = level->testCollision(this, "SolidGround", 0, gravity + 1);
	if (onGround)
	{
		gravity = 0;
	}
	else
	{
		gravity += 0.3;
		pos.y += gravity;
	}

	switch (state)
	{
		case State::Idle:
			currentAnimation = "running";
			if (attemptRunning())
				state = State::Walking;
			if (attemptJumping())
				state = State::Jumping;
			if (attemptSwingWeapon())
				state = State::SwingWeapon;
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			break;
		case State::Walking://????
			currentAnimation = "running";
			if (!attemptRunning())
				state = State::Idle;
			if (attemptJumping())
				state = State::Jumping;
			if (attemptSwingWeapon())
				state = State::SwingWeapon;
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			break;
		case State::Sprinting://maybe make sprinting later
			break;
		case State::Jumping:
			currentAnimation = "jumping";
			attemptRunning(0.75);
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			if (onGround)
				state = State::Idle;
			break;
		case State::SwingWeapon:
			currentArmAnimation = "melee";
			attemptRunning(0.5);
			armAnimations[currentArmAnimation]->advanceFrame();
			if (cooldown == 1)
			{
				armAnimations[currentArmAnimation]->reset();
				state = State::Idle;
			}
			break;
		case State::ThrownWeapon:
			currentArmAnimation = "throw";
			attemptRunning();
			armAnimations[currentArmAnimation]->advanceFrame();
			if (cooldown == 32)
			{
				level->addEntity(new ThrownWeapon(level, pos + je::lengthdir(12, armAngle), config, aim * 12.f));
			}
			else if (cooldown == 1)
			{
				armAnimations[currentArmAnimation]->reset();
				state = State::Idle;
			}
			break;
		case State::Stunned:
			if (cooldown == 1)
				state = State::Idle;
			break;
		default:
			//how?
			break;
	}
	std::cout << "cooldown = " << cooldown << std::endl;
	if (cooldown > 0)
		--cooldown;


	auto bodyAnim = animations.find(currentAnimation);
	if (bodyAnim != animations.end())
	{
		bodyAnim->second->apply([&](sf::Sprite& sprite)
		{
			sprite.setPosition(pos.x, pos.y);
			sprite.setScale(facing, 1);
		});
	}
	armAngle = je::direction(aim);

	auto armAnim = armAnimations.find(currentArmAnimation);
	if (armAnim != armAnimations.end())
	{
		armAnim->second->apply([&](sf::Sprite& sprite)
		{
			sprite.setPosition(pos);
			sprite.setScale(1, facing);
			sprite.setRotation(-armAngle);
		});
	}
	aimer.setPosition(pos + 64.f * aim);
}

bool Player::attemptRunning(float rate)
{
	float speed = 2;
	bool moved = false;
	if (input.isActionHeld("move_left") && !level->testCollision(this, "SolidGround", -speed * rate))
	{
		pos.x -= speed * rate;
		animations[currentAnimation]->advanceFrame();
		facing = Left;
		moved = true;
	}

	if (input.isActionHeld("move_right") && !level->testCollision(this, "SolidGround", speed * rate))
	{
		pos.x += speed * rate;
		animations[currentAnimation]->advanceFrame();
		facing = Right;
		moved = true;
	}
	return moved;
}

bool Player::attemptJumping()
{
	if (level->testCollision(this, "SolidGround", 0, gravity + 1))
	{
		if (input.isActionPressed("jump"))
		{
			gravity = -5;
			return true;
		}
	}
	return false;
}

bool Player::attemptSwingWeapon()
{
	if (input.isActionPressed("swing"))
	{
		cooldown = 64;
		return true;
	}
	return false;
}

bool Player::attemptThrowWeapon()
{
	if (input.isActionHeld("throw"))
	{
		cooldown = 48;
		return true;
	}
	return false;
}

}
