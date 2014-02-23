#include "Player/Player.hpp"

#include <vector>

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Math.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Player/Attack.hpp"
#include "Player/Blood.hpp"
#include "Player/Bone.hpp"
#include "Player/Head.hpp"
#include "Player/Heart.hpp"
#include "Player/PlayerResources.hpp"
#include "Player/ThrownWeapon.hpp"

#include <iostream>

const int RUNNING_ANIM_TIME = 23;

namespace con
{

/*			sword swing anim			*/
std::initializer_list<BoneAnimation::BoneTransform> swordSwingBTarm = {
	BoneAnimation::BoneTransform(60.f),
	BoneAnimation::BoneTransform(30.f),
	BoneAnimation::BoneTransform(45.f),
	BoneAnimation::BoneTransform(55.f)
};

std::initializer_list<BoneAnimation::BoneTransform> swordSwingBTforearm = {
	BoneAnimation::BoneTransform(-60.f),
	BoneAnimation::BoneTransform(-30.f),
	BoneAnimation::BoneTransform(-10.f),
	BoneAnimation::BoneTransform(0.f)
};

std::initializer_list<BoneAnimation::BoneTransform> swordSwingBTsword = {
	BoneAnimation::BoneTransform(-120.f),
	BoneAnimation::BoneTransform(-90.f),
	BoneAnimation::BoneTransform(-60.f),
	BoneAnimation::BoneTransform(-30.f)
};
// temp hack to make invisible while in this anim
std::initializer_list<BoneAnimation::BoneTransform> swordSwingBTknife = {
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f))
};

/*			knife throw anim			*/
std::initializer_list<BoneAnimation::BoneTransform> throwKnifeBTarm = {
	BoneAnimation::BoneTransform(30.f),
	BoneAnimation::BoneTransform(15.f),
	BoneAnimation::BoneTransform(-15.f),
	BoneAnimation::BoneTransform(30.f),
	BoneAnimation::BoneTransform(40.f)
};

std::initializer_list<BoneAnimation::BoneTransform> throwKnifeBTforearm = {
	BoneAnimation::BoneTransform(-45.f),
	BoneAnimation::BoneTransform(-60.f),
	BoneAnimation::BoneTransform(-90.f),
	BoneAnimation::BoneTransform(-60.f),
	BoneAnimation::BoneTransform(-40.f)
};

std::initializer_list<BoneAnimation::BoneTransform> throwKnifeBTknife = {
	BoneAnimation::BoneTransform(-30.f),
	BoneAnimation::BoneTransform(-45.f),
	BoneAnimation::BoneTransform(-30.f),
	BoneAnimation::BoneTransform(0.f),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f))//0 scale
};
// temp hack to make invisible while in this anim
std::initializer_list<BoneAnimation::BoneTransform> throwKnifeBTsword = {
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f))
};

Player::Player(je::Level *level, int x, int y, const PlayerConfig& config, Scoreboard& scores)
	:je::Entity(level, "Player", sf::Vector2f(x, y), sf::Vector2i(16, 24), sf::Vector2i(-8, 0))
	,currentAnimation("running")
	,currentArmAnimation("sword")
	,config(config)
	,input(config.controller)
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
	,veloc(0, 0)
	,onGround(false)
	,arm(new Bone(level, *this, 6, 4, "ninja_arm_segment.png"))
	,forearm(new Bone(level, *this, 6, 4, "ninja_arm_segment.png"))
	,sword(new Bone(level, *this, 16, 4, getSwingingArmSprite(config.sword)))
	,knife(new Bone(level, *this, 8, 3, getThrowingArmSprite(config.thrown)))
{

	armAnimations.insert(std::pair<std::string, BoneAnimation>("melee", BoneAnimation(BoneAnimation::TransformSet(*arm, swordSwingBTarm), 6, false)));
	
	armAnimations.at("melee").addTransformSet(BoneAnimation::TransformSet(*forearm, swordSwingBTforearm));
	armAnimations.at("melee").addTransformSet(BoneAnimation::TransformSet(*sword, swordSwingBTsword));
	armAnimations.at("melee").addTransformSet(BoneAnimation::TransformSet(*knife, swordSwingBTknife));

	armAnimations.insert(std::pair<std::string, BoneAnimation>("throw", BoneAnimation(BoneAnimation::TransformSet(*arm, throwKnifeBTarm), 4, false)));

	armAnimations.at("throw").addTransformSet(BoneAnimation::TransformSet(*forearm, throwKnifeBTforearm));
	armAnimations.at("throw").addTransformSet(BoneAnimation::TransformSet(*sword, throwKnifeBTsword));
	armAnimations.at("throw").addTransformSet(BoneAnimation::TransformSet(*knife, throwKnifeBTknife));

	animations["running"].reset(new je::Animation(level->getGame().getTexManager().get(getClassPrefix(config.type) + "_running.png"), 24, 24, RUNNING_ANIM_TIME));
	animations["running"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(getPos());
		sprite.setOrigin(12, 0);
	});
	animations["jumping"].reset(new je::Animation(level->getGame().getTexManager().get(getClassPrefix(config.type) + "_jumping.png"), 24, 24, 0));
	animations["jumping"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(getPos());
		sprite.setOrigin(12, 0);
	});

	//armAnimations["melee"].reset(new je::Animation(level->getGame().getTexManager().get(getClassPrefix(config.type) + "_" + getSwingingArmSprite(config.sword)), 48, 32, 6, false));
	//armAnimations["melee"]->apply([&](sf::Sprite& sprite)
	//{
	//	sprite.setPosition(getPos());
	//	sprite.setOrigin(24, 10);
	//});
	//armAnimations["throw"].reset(new je::Animation(level->getGame().getTexManager().get(getClassPrefix(config.type) + "_" + getThrowingArmSprite(config.thrown)), 48, 32, 4, false));
	//armAnimations["throw"]->apply([&](sf::Sprite& sprite)
	//{
	//	sprite.setPosition(getPos());
	//	sprite.setOrigin(24, 10);
	//});

	head = new Head(level, getPos().x, getPos().y, *this, scores);
	level->addEntity(head);
	this->setDepth(-6);

	level->addEntity(arm);

	level->addEntity(forearm);

	level->addEntity(sword);

	level->addEntity(knife);

	arm->addChild(forearm);

	forearm->addChild(sword);

	forearm->addChild(knife);

	arm->setDepth(-7);
	forearm->setDepth(-7);
	sword->setDepth(-7);
	knife->setDepth(-7);

	currentArmAnimation = "melee";
}

Player::Facing Player::getFacing() const
{
	return facing;
}

void Player::damage(float amount, const PlayerConfig *source)
{
	health -= amount;
	if (health <= 0)
	{
		//die here
		int n = 16 + je::randomf(16);
		for (int i = 0; i < n; ++i)
			level->addEntity(new Blood(level, getPos(), je::lengthdir(2 + je::randomf(3), je::choose({je::randomf(360), 45 + je::randomf(90)}))));
		level->addEntity(new Heart(level, getPos(), je::lengthdir(3 + je::randomf(4), 60 + je::randomf(60))));

		health = 0;
		if (state != State::Decapitated && source)
			scores.reportKill(*source, config);
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
	//auto it2 = armAnimations.find(currentArmAnimation);
	//if (it2 != armAnimations.end())
	//	it2->second->draw(target, states);
	target.draw(aimer, states);
}

void Player::onUpdate()
{
	//std::cout << "hp: " << health << " / " << maxhealth << std::endl;
	aim.x = input.axisPos("aim_x", getPos().x, level);
	aim.y = input.axisPos("aim_y", getPos().y, level);

	//float newY = level->rayCastManually(this, "SolidGround", [](Entity*e)->bool{return true;}, sf::Vector2f(0, veloc.y)).y;

	onGround = level->testCollision(this, "SolidGround", 0, veloc.y + 1);//newY == getPos().y;
	if (onGround)
	{
		if (veloc.y > 0.f)
		{
			transform().setPosition(prevPos);
			veloc.y = 0.f;
		}
	}
	else
	{
		veloc.y += 0.3f;
		transform().move(0.f, veloc.y);
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
			armAnimations.at(currentArmAnimation).advanceFrame();
			if (armAnimations.at(currentArmAnimation).isFinished())
			{
				armAnimations.at(currentArmAnimation).reset();
				state = State::AttackCooldown;
			}
			break;
		case State::ThrownWeapon:
			currentArmAnimation = "throw";
			attemptRunning();
			if (attemptJumping())
			{
				armAnimations.at(currentArmAnimation).reset();
				state = State::Jumping;
			}
			armAnimations.at(currentArmAnimation).advanceFrame();
			if (cooldown == 32)
			{
				level->addEntity(new ThrownWeapon(level, getPos() + je::lengthdir(12, armAngle), config, aim * 12.f));
				state = State::AttackCooldown;
			}
			break;
		case State::Stunned:
			if (cooldown == 1)
				state = State::Idle;
			break;
		case State::Decapitated:
			attemptRunning(1.5f);
			level->addEntity(new Blood(level, getPos() + sf::Vector2f(0, -4), sf::Vector2f(-3 + je::randomf(6), -je::randomf(16))));
			this->damage(3);//bleedout
			break;
		case State::AttackCooldown:
			attemptRunning(0.9f);
			attemptJumping();
			if (cooldown == 1)
			{
				armAnimations.at(currentArmAnimation).reset();
				state = State::Idle;
			}
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
				this->damage(twep.getDamage(), twep.getPlayerConfig());
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
	}
	{
		std::vector<Entity*> attacks;
		level->findCollisions(attacks, this, "Attack");
		for (je::Entity *entity : attacks)
		{
			Attack& atk = *((Attack*) entity);
			if (atk.getPlayerConfig().team != this->config.team)
			{
				this->damage(atk.getDamage(), &atk.getPlayerConfig());
				const int n = je::randomf(15) + 3;
				for (int i = 0; i < n; ++i)
				{
					level->addEntity(new Blood(level, getPos(), je::lengthdir(je::randomf(3 + je::randomf(9)), je::randomf(360)) - sf::Vector2f(0, 2)));
				}
				atk.destroy();
			}
		}
	}
	//	to stop walking off map
	if (getPos().x < 32)
		transform().setPosition(32, getPos().y);
	if (getPos().x > level->getWidth() - 32)
		transform().setPosition(level->getWidth() - 32, getPos().y);
	//	and then fix up the sprites
	auto bodyAnim = animations.find(currentAnimation);
	if (bodyAnim != animations.end())
	{
		bodyAnim->second->apply([&](sf::Sprite& sprite)
		{
			sprite.setPosition(getPos());
			sprite.setScale(facing, 1);
		});
	}
	armAngle = je::direction(aim);

	//auto armAnim = armAnimations.find(currentArmAnimation);
	//if (armAnim != armAnimations.end())
	//{
	//	armAnim->second->apply([&](sf::Sprite& sprite)
	//	{
	//		sprite.setPosition(getPos());
	//		sprite.setScale(1, facing);
	//		sprite.setRotation(-armAngle);
	//	});
	//}

	armAnimations.at(currentArmAnimation).transformBones();//-armAngle, sf::Vector2f(1.f, facing));

	armAnimations.at(currentArmAnimation).scaleRotations(facing);

	sf::Transformable& transform = arm->boneTransform();

	transform.setPosition(getPos());
	transform.scale(1.f, facing);
	transform.rotate(-armAngle);

	aimer.setPosition(getPos() + 64.f * aim);
}

void Player::reset()
{
	health = maxhealth;
	transform().setPosition(je::random(level->getWidth()), -32.f);
	state = State::Idle;
	currentAnimation = "running";
	cooldown = 0;
	if (head)
	{
		head->destroy();
	}
	head = new Head(level, getPos().x, getPos().y, *this, scores);
	level->addEntity(head);
}

bool Player::attemptRunning(float rate)
{
	const float highestWalkableSlopeRatio = 4.f;
	const int highestWalkableSlope = highestWalkableSlopeRatio * abs(veloc.x);
	const float horizontalAcceleration = 0.2;
	const float maxHorizontalSpeed = 2.5 * rate;

	bool moved = false;

	if (input.isActionHeld("move_left") && !input.isActionHeld("move_right"))
	{
		facing = Left;
		veloc.x -= horizontalAcceleration;
	}
	else if (input.isActionHeld("move_right"))
	{
		facing = Right;
		veloc.x += horizontalAcceleration;
	}
	else
	{
		const float friction = onGround ? 0.15 : 0.05;
		if (veloc.x > friction)
			veloc.x -= friction;
		else if (veloc.x < -friction)
			veloc.x += friction;
		else
			veloc.x = 0;
	}
	je::limit(veloc.x, -maxHorizontalSpeed, maxHorizontalSpeed);
	
	if (veloc.x > 0.1f || veloc.x < -0.1f)
	{
		for (int i = 0; i < highestWalkableSlope; ++i)
		{
			if (!level->testCollision(this, "SolidGround", veloc.x, -i))
			{
				transform().move(veloc.x, -i);
				moved = true;
				break;
			}
		}
	}
	if (moved)
	{
		for (int i = 0; i < abs(veloc.x); ++i)
		{
			animations[currentAnimation]->advanceFrame();
		}
	}
	return moved;
}

bool Player::attemptJumping()
{
	if (level->testCollision(this, "SolidGround", 0, veloc.y + 1))
	{
		if (input.isActionPressed("jump"))
		{
			transform().move(0, -5);
			veloc.y = -5;
			return true;
		}
	}
	return false;
}

bool Player::attemptSwingWeapon()	
{
	if (input.isActionPressed("swing"))
	{
		level->addEntity(new Attack(level, &getPos(), sf::Vector2f(-6, -16) + je::lengthdir(4, armAngle), sf::Vector2i(12, 12), config, 32, 35, sf::Vector2f(facing * 0.4, 0.25)));
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
