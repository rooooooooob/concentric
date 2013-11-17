#ifndef CON_PLAYER_HPP
#define CON_PLAYER_HPP

#include <map>
#include <string>
#include <memory>
#include "Entity.hpp"
#include "Animation.hpp"
#include "Controller.hpp"
#include "PlayerConfig.hpp"

namespace con
{

class Head;

class Player : public je::Entity
{
public:
	enum Facing
	{
		Left = -1,
		Right = 1
	};
	Player(je::Level *level, int x, int y, const PlayerConfig& config);

	Facing getFacing() const;

	void damage(float amount);

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;

	void reset();

	bool attemptRunning(float rate = 1.f);

	bool attemptJumping();

	bool attemptSwingWeapon();

	bool attemptThrowWeapon();

	enum class State
	{
		Idle,
		Walking,
		Sprinting,
		Jumping,
		SwingWeapon,
		ThrownWeapon,
		Stunned,
		Decapitated
	};


	std::string currentAnimation;
	std::map<std::string, std::unique_ptr<je::Animation> > animations;
	std::string currentArmAnimation;
	std::map<std::string, std::unique_ptr<je::Animation> > armAnimations;
	sf::Sprite aimer;
	const je::Controller& input;
	const PlayerConfig& config;
	float gravity;
	float armAngle;
	sf::Vector2f aim;
	Facing facing;
	State state;
	int cooldown;
	Head *head;
	float health;
	float maxhealth;
};

}

#endif
