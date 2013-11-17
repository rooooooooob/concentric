#include "Blood.hpp"


#include <sstream>
#include "Level.hpp"
#include "Game.hpp"

namespace con
{

Blood::Blood(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc, int type)
	:je::Entity(level, "Blood", pos, sf::Vector2i(3, 3), sf::Vector2i(-1, -1))
	,veloc(veloc)
	,timer(360)
{
	std::stringstream ss;
	ss << "blood"
	   << type
	   << ".png";
	sprite.setTexture(level->getGame().getTexManager().get(ss.str()));
	sprite.setOrigin(3, 3);
	this->setDepth(-10000);
}

void Blood::onUpdate()
{
	if (--timer < 0)
	this->destroy();
	if (!level->testCollision(this, "SolidGround"))
	{
		veloc.y += 0.2;
		pos += veloc;
	}
	if (pos.x < -16 || pos.x > level->getWidth() + 16)
		this->destroy();

	sprite.setPosition(pos);
}

void Blood::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite, states);
}

}
