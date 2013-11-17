#include "Head.hpp"

#include "Game.hpp"
#include "Level.hpp"

namespace con
{

Head::Head(je::Level *level, int x, int y, Player& owner)
	:je::Entity(level, "Head", sf::Vector2f(x, y), sf::Vector2i(8, 8), sf::Vector2i(-4, -6))
	,owner(owner)
	,sprite(level->getGame().getTexManager().get("ninja_head.png"))
{
	sprite.setOrigin(4, 4);
	sprite.setPosition(pos);
	this->setDepth(-5);
}

void Head::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite, states);
}

void Head::onUpdate()
{
	pos = owner.getPos();
	sprite.setPosition(pos.x, pos.y - 4);
	sprite.setScale(owner.getFacing(), 1);
}

}
