#include "Scenery.hpp"

#include "Core/Game.hpp"
#include "Core/Level.hpp"

namespace con
{

Scenery::Scenery(je::Level * level, int x, int y, const std::string& fname)
	:je::Entity(level, "Scenery", sf::Vector2f(x, y), sf::Vector2i())
	,sprite(level->getGame().getTexManager().get(fname))
{
	sprite.setPosition(x, y);
}

void Scenery::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite);
}

void Scenery::onUpdate()
{
}

}
