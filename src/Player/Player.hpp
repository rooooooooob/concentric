#ifndef CON_PLAYER_HPP
#define CON_PLAYER_HPP

#include <map>
#include <string>
#include <memory>

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"
#include "jam-engine/Core/Controller.hpp"

#include "Player/BoneAnimation.hpp"
#include "Player/PlayerConfig.hpp"
#include "Scoreboard.hpp"



namespace con
{

class Head;

class Bone;

class Player : public je::Entity
{
public:
	enum Facing
	{
		Left = -1,
		Right = 1
	};
	Player(je::Level *level, int x, int y, const PlayerConfig& config, Scoreboard& scores);

	Facing getFacing() const;

	void damage(float amount, const PlayerConfig* source = nullptr);

	const PlayerConfig& getConfig() const;

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;

	void reset();

	bool attemptRunning(float rate = 1.f);

	bool attemptJumping();

	bool attemptSwingWeapon(float amplifier = 1.f);

	bool attemptThrowWeapon();

	bool involuntaryRunning(float rate = 1.f);

	enum class State
	{
		Idle,
		Walking,
		Sprinting,
		Jumping,
		Leaping,
		SwingWeapon,
		SprintSwingWeapon,
		ThrownWeapon,
		Stunned,
		Decapitated,
		AttackCooldown
	};


	std::string currentAnimation;
	std::map<std::string, std::unique_ptr<je::Animation> > animations;
	std::string currentArmAnimation;
	std::map<std::string, BoneAnimation> armAnimations;
	std::vector<sf::Sprite> crosshair;
	const je::Controller& input;
	const PlayerConfig& config;
	float armAngle;
	sf::Vector2f aim;
	Facing facing;
	State state;
	int cooldown;
	Scoreboard& scores;
	Head *head;
	float health;
	float maxhealth;
	sf::Vector2f veloc;
	bool onGround;
	Bone *arm, *forearm, *sword, *knife;
	float rangedInaccuracy;
	std::function<bool(const Entity*)> jumpThroughFilter;
};

}

#endif
