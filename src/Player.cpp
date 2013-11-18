#include "Player.hpp"

#include <vector>
#include "Level.hpp"
#include "Game.hpp"
#include "Trig.hpp"
#include "Head.hpp"
#include "ThrownWeapon.hpp"
#include "Blood.hpp"
#include "Random.hpp"
#include "Heart.hpp"
#include "Attack.hpp"
#include <iostream>

const int RUNNING_ANIM_TIME = 11;

namespace con
{

Player::Player(je::Level *level, int x, int y, const PlayerConfig& config, Scoreboard& scores)
	:je::Entity(level, "Player", sf::Vector2f(x, y), sf::Vector2i(16, 24), sf::Vector2i(-8, 2))
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
	,head(nullptr)
	,health(100)
	,maxhealth(health)
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

	armAnimations["melee"].reset(new je::Animation(level->getGame().getTexManager().get("ninja_katana.png"), 48, 32, 9, false));
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

	head = new Head(level, pos.x, pos.y, *this);
	level->addEntity(head);
	this->setDepth(-6);

	currentArmAnimation = "melee";
}

Player::Facing Player::getFacing() const
{
	return facing;
}

void Player::damage(float amount)
{
	health -= amount;
	if (health <= 0)
	{
		//die here
		int n = 16 + je::randomf(16);
        for (int i = 0; i < n; ++i)
            level->addEntity(new Blood(level, pos, je::lengthdir(2 + je::randomf(3), je::choose({je::randomf(360), 45 + je::randomf(90)}))));
        level->addEntity(new Heart(level, pos, je::lengthdir(3 + je::randomf(4), 60 + je::randomf(60))));

		health = 0;
		this->reset();
	}
}

const PlayerConfig& Player::getConfig() const
{
	return config;
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
	//std::cout << "hp: " << health << " / " << maxhealth << std::endl;
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

	if (state != State::Decapitated && head->getState() == Head::State::Decapitated)
	{
		state = State::Decapitated;
		head = nullptr;
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
			if (attemptJumping())
			{
				armAnimations[currentArmAnimation]->reset();
				state = State::Jumping;
			}
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
		case State::Decapitated:
			attemptRunning(1.5f);
			level->addEntity(new Blood(level, pos + sf::Vector2f(0, -4), sf::Vector2f(-3 + je::randomf(6), -je::randomf(16))));
			this->damage(3);//bleedout
			break;
		default:
			//how?
			break;
	}
	if (cooldown > 0)
		--cooldown;

	//	now check for pointy things stabbing you
	{
		std::vector<Entity*> thrownWeapons;
		level->findCollisions(thrownWeapons, this, "ThrownWeapon");
		for (je::Entity *entity : thrownWeapons)
		{
			ThrownWeapon& twep = *((ThrownWeapon*) entity);
			if (twep.getTeamID() != this->config.team)
			{
				this->damage(twep.getDamage());
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
	}
	{
		std::vector<Entity*> attacks;
		level->findCollisions(attacks, this, "Attack");
		for (je::Entity *entity : attacks)
		{
			Attack& atk = *((Attack*) entity);
			if (atk.getTeam() != this->config.team)
			{
				this->damage(atk.getDamage());
				const int n = je::randomf(15) + 3;
				for (int i = 0; i < n; ++i)
				{
					level->addEntity(new Blood(level, pos, je::lengthdir(je::randomf(3 + je::randomf(9)), je::randomf(360)) - sf::Vector2f(0, 2)));
				}
				atk.destroy();
			}
		}
	}

	//	and then fix up the sprites
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

void Player::reset()
{
	health = maxhealth;
	pos.x = je::random(level->getWidth());
	pos.y = -32.f;
	state = State::Idle;
	currentAnimation = "running";
	cooldown = 0;
	if (head)
	{
		head->destroy();
	}
	head = new Head(level, pos.x, pos.y, *this);
	level->addEntity(head);
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
	if (input.isActionPressed("swing") && cooldown == 0)
	{
		level->addEntity(new Attack(level, &pos, sf::Vector2f(-6, -16) + je::lengthdir(4, armAngle), sf::Vector2i(12, 12), config.team, 32, 35, sf::Vector2f(facing * 0.4, 0.25)));
		cooldown = 64;
		return true;
	}
	return false;
}

bool Player::attemptThrowWeapon()
{
	if (input.isActionHeld("throw") && cooldown == 0)
	{
		cooldown = 48;
		return true;
	}
	return false;
}

}
