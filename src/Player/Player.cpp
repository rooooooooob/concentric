#include "Player/Player.hpp"

#include <vector>

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Math.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Level/JumpThroughPlatform.hpp"
#include "Level/Powerup.hpp"
#include "Player/Attack.hpp"
#include "Player/Blood.hpp"
#include "Player/Bone.hpp"
#include "Player/Head.hpp"
#include "Player/Heart.hpp"
#include "Player/GrapplingHook.hpp"
#include "Player/PlayerResources.hpp"
#include "Player/ThrownWeapon.hpp"

#include <iostream>

const int RUNNING_ANIM_TIME = 23;

const float AIMER_MAX_DISTANCE = 96.f;

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
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f))
};

/*			running slash anim			*/
std::initializer_list<BoneAnimation::BoneTransform> sprintSlashBTarm = {
	BoneAnimation::BoneTransform(45.f),
	BoneAnimation::BoneTransform(15.f),
	BoneAnimation::BoneTransform(-15.f),
	BoneAnimation::BoneTransform(-45.f)
};

std::initializer_list<BoneAnimation::BoneTransform> sprintSlashBTforearm = {
	BoneAnimation::BoneTransform(60.f),
	BoneAnimation::BoneTransform(45.f),
	BoneAnimation::BoneTransform(30.f),
	BoneAnimation::BoneTransform(15.f)
};

std::initializer_list<BoneAnimation::BoneTransform> sprintSlashBTsword = {
	BoneAnimation::BoneTransform(35.f, sf::Vector2f(1.f, -1.f)),
	BoneAnimation::BoneTransform(25.f, sf::Vector2f(1.f, -1.f)),
	BoneAnimation::BoneTransform(15.f, sf::Vector2f(1.f, -1.f)),
	BoneAnimation::BoneTransform(5.f, sf::Vector2f(1.f, -1.f))
};
// temp hack to make invisible while in this anim
std::initializer_list<BoneAnimation::BoneTransform> sprintSlashBTknife = {
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f)),
	BoneAnimation::BoneTransform(0.f, sf::Vector2f(0.f, 0.f))
};

/*			sword thrust anim			*/
std::initializer_list<BoneAnimation::BoneTransform> thrustBTarm = {
	BoneAnimation::BoneTransform(-200.f),
	BoneAnimation::BoneTransform(-225.f),
	BoneAnimation::BoneTransform(-290.f),
	BoneAnimation::BoneTransform(-320.f)
};

std::initializer_list<BoneAnimation::BoneTransform> thrustBTforearm = {
	BoneAnimation::BoneTransform(-80.f),
	BoneAnimation::BoneTransform(-100.f),
	BoneAnimation::BoneTransform(-45.f),
	BoneAnimation::BoneTransform(-20.f)
};

std::initializer_list<BoneAnimation::BoneTransform> thrustBTsword = {
	BoneAnimation::BoneTransform(-75.f),
	BoneAnimation::BoneTransform(-35.f),
	BoneAnimation::BoneTransform(-25.f),
	BoneAnimation::BoneTransform(-10.f)
};
// temp hack to make invisible while in this anim
std::initializer_list<BoneAnimation::BoneTransform> thrustBTknife = {
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
	,currentArmAnimation("melee")
	,crosshair(4, sf::Sprite(level->getGame().getTexManager().get("aimer.png")))
	,input(config.controller)
	,config(config)
	,armAngle(0)
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
	,rangedInaccuracy(0.f)
	,jumpThroughFilter([this](const Entity* e)->bool {
		return ((const JumpThroughPlatform*)e)->isSolid(*this);
	})
	,threeshotcooldown(0)
	,bigweaponcooldown(0)
	,hpbarback(sf::Vector2f(32, 3))
	,hpbarfront(sf::Vector2f(32, 3))
	,hook(nullptr)
{

	armAnimations.insert(std::pair<std::string, BoneAnimation>("melee", BoneAnimation(BoneAnimation::TransformSet(*arm, swordSwingBTarm), 6, false)));
	
	armAnimations.at("melee").addTransformSet(BoneAnimation::TransformSet(*forearm, swordSwingBTforearm));
	armAnimations.at("melee").addTransformSet(BoneAnimation::TransformSet(*sword, swordSwingBTsword));
	armAnimations.at("melee").addTransformSet(BoneAnimation::TransformSet(*knife, swordSwingBTknife));

	armAnimations.insert(std::pair<std::string, BoneAnimation>("sprint_melee", BoneAnimation(BoneAnimation::TransformSet(*arm, sprintSlashBTarm), 7, false)));
	
	armAnimations.at("sprint_melee").addTransformSet(BoneAnimation::TransformSet(*forearm, sprintSlashBTforearm));
	armAnimations.at("sprint_melee").addTransformSet(BoneAnimation::TransformSet(*sword, sprintSlashBTsword));
	armAnimations.at("sprint_melee").addTransformSet(BoneAnimation::TransformSet(*knife, sprintSlashBTknife));

	armAnimations.insert(std::pair<std::string, BoneAnimation>("thrust", BoneAnimation(BoneAnimation::TransformSet(*arm, thrustBTarm), 7, false)));
	
	armAnimations.at("thrust").addTransformSet(BoneAnimation::TransformSet(*forearm, thrustBTforearm));
	armAnimations.at("thrust").addTransformSet(BoneAnimation::TransformSet(*sword, thrustBTsword));
	armAnimations.at("thrust").addTransformSet(BoneAnimation::TransformSet(*knife, thrustBTknife));


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
	animations["leaping"].reset(new je::Animation(level->getGame().getTexManager().get(getClassPrefix(config.type) + "_leaping.png"), 32, 32, 0));
	animations["leaping"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(getPos());
		sprite.setOrigin(24, 7);
	});

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

	for (int i = 0, size = crosshair.size(); i < size; ++i)
	{
		crosshair[i].setRotation(360.f * i / size);
	}

	hpbarback.setFillColor(sf::Color::Black);
	hpbarback.setOutlineColor(sf::Color::White);
	hpbarback.setOutlineThickness(1);
	hpbarback.setOrigin(16, 0);

	hpbarfront.setFillColor(sf::Color::Red);
	hpbarfront.setOrigin(16, 0);
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
	for (const sf::Sprite& aimer : crosshair)
		target.draw(aimer, states);

	target.draw(hpbarback);
	target.draw(hpbarfront);
}

void Player::onUpdate()
{
	if (threeshotcooldown > 0)
		--threeshotcooldown;
	if (bigweaponcooldown > 0)
		--bigweaponcooldown;
	Powerup *powerup = static_cast<Powerup*>(level->testCollision(this, "Powerup"));
	if (powerup)
	{
		switch (powerup->getType())
		{
		case Powerup::Type::ThreeShot:
			threeshotcooldown += 300;
			break;
		case Powerup::Type::Health:
			health += 100;
			break;
		case Powerup::Type::BigWeapon:
			bigweaponcooldown += 900;
			break;
		}
		powerup->destroy();	
	}
	//std::cout << "hp: " << health << " / " << maxhealth << std::endl;
	const sf::Vector2f newAim(input.axisPos("aim_x", getPos().x, level), input.axisPos("aim_y", getPos().y, level));
	if (je::length(newAim) > 0.1f)
		aim = newAim;

	//float newY = level->rayCastManually(this, "SolidGround", [](Entity*e)->bool{return true;}, sf::Vector2f(0, veloc.y)).y;

	const bool jumpThroughBelow = (level->testCollision(this, "JumpThroughPlatform", jumpThroughFilter, 0, veloc.y + 1) != nullptr);

	onGround = jumpThroughBelow || level->testCollision(this, "SolidGround", 0, veloc.y + 1);
	
	if (jumpThroughBelow && input.isActionHeld("crouch"))
	{
		transform().move(0.f, 2.f);
		onGround = false;
	}
	
	bool retractingHook = false;
	if (hook)
	{
		if (input.isActionHeld("grappling"))
		{
			if (hook->pullIn())
			{
				hook->destroy();
				hook = nullptr;
			}
			retractingHook = true;
		}
		if (input.isActionReleased("grappling"))
		{
			hook->destroy();
			hook = nullptr;
		}
	}
	else
	{
		if (input.isActionReleased("grappling"))
		{
			sf::Vector2f projectileVelocity(je::lengthdir(je::length(aim) * 12.f, je::direction(aim)));
			hook = new GrapplingHook(*this, getPos(), projectileVelocity);
			level->addEntity(hook);
		}
	}

	if (onGround)
	{
		if (veloc.y > 0.f)
		{
			//transform().setPosition(prevPos);
			veloc.y = 0.f;
		}
	}
	else if (retractingHook)
	{
		// nothing
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
			if (attemptThrustWeapon())
				state = State::ThrustWeapon;
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			break;
		case State::Walking:
			currentAnimation = "running";
			if (!attemptRunning())
				state = State::Idle;
			if (input.isActionHeld("sprint"))
				state = State::Sprinting;
			if (attemptJumping())
				state = State::Jumping;
			if (attemptSwingWeapon())
				state = State::SwingWeapon;
			if (attemptThrustWeapon())
				state = State::ThrustWeapon;
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			break;
		case State::Sprinting:
			currentAnimation = "running";
			currentArmAnimation = "sprint_melee";
			aim.x = facing / 2.f;
			aim.y = 0.f;
			if (!attemptRunning(2.f))
				state = State::Idle;
			if (!input.isActionHeld("sprint"))
				state = State::Walking;
			if (attemptJumping())
				state = State::Leaping;
			if (attemptSwingWeapon(1.5f))
				state = State::SprintSwingWeapon;
			if (attemptThrustWeapon(1.5f))
				state = State::SprintThrustWeapon;
			break;
		case State::Jumping:
			currentAnimation = "jumping";
			attemptRunning(0.75);
			if (attemptThrustWeapon())
				state = State::ThrustWeapon;
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			if (attemptThrustWeapon())
				state = State::SprintThrustWeapon;
			if (attemptSwingWeapon())
				state = State::SprintSwingWeapon;
			if (input.isActionHeld("crouch"))
			{
				state = State::DownwardThrust;
				atk = new Attack(level, *sword, config, 9999, 135);
				level->addEntity(atk);
			}
			if (onGround)
				state = State::Idle;
			break;
		case State::Leaping:
			//currentAnimation = "leaping";
			//animations.at(currentAnimation)->setRotation(90.f - je::direction(veloc));
			//head->transform().setRotation(90.f - je::direction(veloc));
			involuntaryRunning(2.f * facing);
			if (attemptThrowWeapon())
				state = State::ThrownWeapon;
			if (attemptThrustWeapon())
				state = State::SprintThrustWeapon;
			if (attemptSwingWeapon())
				state = State::SprintSwingWeapon;
			if (input.isActionHeld("crouch"))
			{
				state = State::DownwardThrust;
				atk = new Attack(level, *sword, config, 9999, 135);
				level->addEntity(atk);
			}
			if (onGround)
			{
				state = State::Idle;
				//animations.at(currentAnimation)->setRotation(0.f);
			}
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
		case State::SprintSwingWeapon:
			involuntaryRunning(2.f);
			currentArmAnimation = "sprint_melee";
			aim.x = facing;
			aim.y = 0.f;
			armAnimations.at(currentArmAnimation).advanceFrame();
			if (armAnimations.at(currentArmAnimation).isFinished())
			{
				armAnimations.at(currentArmAnimation).reset();
				state = State::AttackCooldown;
			}
			break;
		case State::SprintThrustWeapon:
			involuntaryRunning(2.f);
			currentArmAnimation = "thrust";
			aim.x = facing;
			aim.y = 0.f;
			armAnimations.at(currentArmAnimation).advanceFrame();
			if (armAnimations.at(currentArmAnimation).isFinished())
			{
				armAnimations.at(currentArmAnimation).reset();
				state = State::AttackCooldown;
			}
			break;
		case State::ThrustWeapon:
			currentArmAnimation = "thrust";
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
			if (threeshotcooldown > 0)
				armAnimations.at(currentArmAnimation).advanceFrame();
			armAnimations.at(currentArmAnimation).advanceFrame();
			if (cooldown == (threeshotcooldown > 0 ? 16 : 32))
			{
				if (threeshotcooldown == 0)
				{
					float variance = 2.f * je::randomf(rangedInaccuracy) - rangedInaccuracy;
					sf::Vector2f projectileVelocity(je::lengthdir(je::length(aim) * 12.f, je::direction(aim) + variance));
					level->addEntity(new ThrownWeapon(level, getPos() + je::lengthdir(12, armAngle + variance), config, projectileVelocity));
				}
				else
				{
					for (int i = -1; i < 2; ++i)
					{
						const int variance = 15 * i;
						sf::Vector2f projectileVelocity(je::lengthdir(je::length(aim) * 12.f, je::direction(aim) + variance));
						level->addEntity(new ThrownWeapon(level, getPos() + je::lengthdir(12, armAngle + 2 * variance), config, projectileVelocity));
					}
				}
				state = State::AttackCooldown;
			}
			break;
		case State::Stunned:
			if (cooldown == 1)
				state = State::Idle;
			break;
		case State::Decapitated:
			if (input.isActionPressed("move_right"))
				facing = Right;
			if (input.isActionPressed("move_left"))
				facing = Left;
			veloc.x = 3.f * facing;
			involuntaryRunning(1.5f);
			if (cooldown <= 1)
				attemptThrowWeapon();
			if (cooldown <= 1)
				attemptSwingWeapon();
			if (cooldown <= 1) 
				attemptThrustWeapon();
			level->addEntity(new Blood(level, getPos() + sf::Vector2f(0, -4), sf::Vector2f(-3 + je::randomf(6), -je::randomf(16))));
			this->damage(2);//bleedout
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
		case State::DownwardThrust:
			veloc.y += 0.3;
			currentArmAnimation = "thrust";
			aim.x = facing * 0.1;
			aim.y = 1;
			if (onGround)
			{
				state = State::Idle;
				atk->destroy();
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
				const int n = je::randomf(atk.getDamage() / 1.5f) + 3;
				for (int i = 0; i < n; ++i)
				{
					level->addEntity(new Blood(level, getPos(), je::lengthdir(je::randomf(3 + je::randomf(9)), je::randomf(360)) - sf::Vector2f(0, 2)));
				}
				atk.destroy();
			}
		}
	}
	//	to stop walking off map
	if (getPos().x < 8.f)
	{
		transform().setPosition(8.f, getPos().y);
		if (veloc.x < 0.f)
			veloc.x = 0.f;
	}
	else if (getPos().x > level->getWidth() - 8.f)
	{
		transform().setPosition(level->getWidth() - 8.f, getPos().y);
		if (veloc.x > 0.f)
			veloc.x = 0.f;
	}
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


	armAnimations.at(currentArmAnimation).transformBones();

	armAnimations.at(currentArmAnimation).scaleRotations(facing);


	if (bigweaponcooldown > 0 && sword->boneTransform().getScale().x != 0.f)
	{
		sword->boneTransform().setScale(2.f, 2.f);
	}

	sf::Transformable& transform = arm->boneTransform();

	transform.setPosition(getPos());
	transform.scale(1.f, facing);
	transform.rotate(-armAngle);

	const float rangedVarianceMin = abs(veloc.x) * 8.f;
	if (rangedVarianceMin < rangedInaccuracy)
	{
		rangedInaccuracy -= 0.75f;
		if (rangedInaccuracy < rangedVarianceMin)
			rangedInaccuracy = rangedVarianceMin;
	}
	else
		rangedInaccuracy = rangedVarianceMin;


	for (sf::Sprite& aimer : crosshair)
	{
		aimer.setPosition(getPos() + AIMER_MAX_DISTANCE * aim);
		// calculates the opposite side of a right-angle triangle given the adjacent and the angle between adjacent/hypotenuse
		// this is so given the angle variance of a shot, we can make the distance between crosshairs be far enough that they
		// are equal to the maxium variance of a shot, so the shot should always pass through the two crosshairs
		// (if they were perpendicular to the aiming direction, that is)
		aimer.setOrigin(sinf(rangedInaccuracy * je::pi / 180.f) * AIMER_MAX_DISTANCE / sinf((90.f - rangedInaccuracy) * je::pi / 180.f), 5.f);
		aimer.rotate(0.3f);
	}



	hpbarback.setPosition(getPos().x, getPos().y - 64);
	hpbarback.setSize(sf::Vector2f(health > maxhealth ? health / 100.f * 32 : 32, hpbarback.getSize().y));
	hpbarfront.setPosition(getPos().x, getPos().y - 64);
	hpbarfront.setSize(sf::Vector2f(health / 100.f * 32, hpbarfront.getSize().y));
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
	if (bigweaponcooldown > 0)
		rate *= 1.15;
	const float horizontalAcceleration = 0.2;
	const float maxHorizontalSpeed = 2 * rate;

	

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
	
	bool moved = involuntaryRunning(rate);

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
	if (level->testCollision(this, "SolidGround", 0, veloc.y + 1) ||
		level->testCollision(this, "JumpThroughPlatform", jumpThroughFilter, 0, veloc.y + 1))
	{
		if (input.isActionPressed("jump"))
		{
			transform().move(0, -5);
			veloc.y = -5.f - abs(veloc.x) / 2.f;
			return true;
		}
	}
	return false;
}

bool Player::attemptSwingWeapon(float amplifier)	
{
	if (bigweaponcooldown > 0)
		amplifier *= 1.75;
	if (input.isActionPressed("swing"))
	{
		level->addEntity(new Attack(level, *sword, config, 6 * 4, amplifier * 35));
		cooldown = 64;
		return true;
	}
	return false;
}

bool Player::attemptThrustWeapon(float amplifier)	
{
	if (bigweaponcooldown > 0)
		amplifier *= 2;
	if (input.isActionPressed("thrust"))
	{
		level->addEntity(new Attack(level, *sword, config, 5 * 4, amplifier * 25));
		cooldown = 48;
		return true;
	}
	return false;
}

bool Player::attemptThrowWeapon()
{
	if (input.isActionHeld("throw"))
	{
		cooldown = (threeshotcooldown > 0 ? 20 : 48);
		return true;
	}
	return false;
}

bool Player::involuntaryRunning(float rate)
{
	const float highestWalkableSlopeRatio = 4.f;
	const int highestWalkableSlope = highestWalkableSlopeRatio * abs(veloc.x);
	
	if (veloc.x > 0.1f || veloc.x < -0.1f)
	{
		for (int i = 0; i < highestWalkableSlope; ++i)
		{
			if (!level->testCollision(this, "SolidGround", veloc.x, -i))
			{
				transform().move(veloc.x, -i);
				return true;
			}
		}
	}
	return false;
}

}
