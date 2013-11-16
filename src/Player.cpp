#include "Player.hpp"

#include "Level.hpp"
#include "Game.hpp"
#include <iostream>

const int RUNNING_ANIM_TIME = 6;

namespace con
{

Player::Player(je::Level *level, int x, int y, int team, const PlayerConfig& config, const je::Controller& controller)
	:je::Entity(level, "Player", sf::Vector2f(x, y), sf::Vector2i(16, 24))
	,currentAnimation("running")
	,input(controller)
{
	animations["running"].reset(new je::Animation(level->getGame().getTexManager().get("running_blue.png"), 24, 24, RUNNING_ANIM_TIME));
	animations["running"]->apply([&](sf::Sprite& sprite)
	{
		sprite.setPosition(pos.x, pos.y);
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
	if (animations[currentAnimation])
	{
		animations[currentAnimation]->apply([&](sf::Sprite& sprite)
		{
			sprite.setPosition(pos.x, pos.y);
		});
	}
}

}