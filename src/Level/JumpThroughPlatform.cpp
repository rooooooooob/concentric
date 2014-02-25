#include "Level/JumpThroughPlatform.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"

namespace con
{

JumpThroughPlatform::JumpThroughPlatform(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "JumpThroughPlatform", pos, sf::Vector2i(32, 6))
	,sprite(level->getGame().getTexManager().get("platform.png"))
{
	sprite.setPosition(pos);
}

JumpThroughPlatform::JumpThroughPlatform(je::Level * level, int x, int y, sf::Rect<int> bounds, const std::string& fname)
	:je::Entity(level, "JumpThroughPlatform", sf::Vector2f(bounds.left, bounds.top), sf::Vector2i(bounds.width, bounds.height), sf::Vector2i(x - bounds.left, y - bounds.top))
	,sprite(level->getGame().getTexManager().get(fname))
{
	sprite.setPosition(x, y);
}


bool JumpThroughPlatform::isSolid(const je::Entity& entity) const
{
	const float deltaY = entity.getPos().y - entity.getPrevPos().y;

	const float thisTop = this->getBounds().top;

	const float otherBottom = entity.getBounds().top + entity.getBounds().height - deltaY;

	return otherBottom <= thisTop;
}




void JumpThroughPlatform::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite);
}

void JumpThroughPlatform::onUpdate()
{
}

}
