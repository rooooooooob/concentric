#include "Player/Blood.hpp"


#include <sstream>
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

namespace con
{

Blood::Blood(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc, int type)
	:je::Entity(level, "Blood", pos, sf::Vector2i(3, 3), sf::Vector2i(-1, -1))
	,veloc(veloc)
	,timer(360)
	,isStuck(false)
{
	std::stringstream ss;
	ss << "blood"
	   << type
	   << ".png";
	sprite.setTexture(level->getGame().getTexManager().get(ss.str()));
	sprite.setOrigin(3, 3);
	sprite.setPosition(pos);
	this->setDepth(-10000);
}

void Blood::onUpdate()
{
	if (--timer < 0)
		this->destroy();
	if (!isStuck)
	{
		if (level->testCollision(this, "SolidGround"))
		{
			isStuck = true;
		}
		else
		{
			veloc.y += 0.2;
			transform().move(veloc);

			if (getPos().x < -16 || getPos().x > level->getWidth() + 16)
				this->destroy();

			sprite.setPosition(getPos());
		}
	}
}

void Blood::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite, states);
}

}
