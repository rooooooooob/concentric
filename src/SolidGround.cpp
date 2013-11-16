#include "SolidGround.hpp"

#include "Game.hpp"
#include "Level.hpp"

namespace con
{

SolidGround::SolidGround(je::Level * level, int x, int y, sf::Rect<int> bounds, const std::string& fname)
	:je::Entity(level, "SolidGround", sf::Vector2f(bounds.left, bounds.top), sf::Vector2i(bounds.width, bounds.height), sf::Vector2i(x - bounds.left, y - bounds.top))
	,sprite(level->getGame().getTexManager().get(fname))
{
}

void SolidGround::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite);
}

void SolidGround::onUpdate()
{
}

}
