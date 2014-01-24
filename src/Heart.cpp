#include "Heart.hpp"

#include <cmath>
#include "Blood.hpp"
#include "Core/Level.hpp"
#include "Core/Game.hpp"
#include "Utility/Trig.hpp"
#include "Utility/Random.hpp"

namespace con
{

Heart::Heart(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc)
	:je::Entity(level, "Heart", pos, sf::Vector2i(7, 7), sf::Vector2i(-3, -3))
	,in(level->getGame().getTexManager().get("heart0.png"))
	,out(level->getGame().getTexManager().get("heart1.png"))
	,timer(900)
	,veloc(veloc)
{
}

void Heart::onUpdate()
{
	if (--timer < 0)
		this->destroy();
	if (!level->testCollision(this, "SolidGround", veloc.x, veloc.y))
	{
		veloc.y += 0.1;
		pos += veloc;
		sprite.rotate(0.1);
	}
	if (pos.x < -32 || pos.x > level->getWidth() + 32)
		this->destroy();
	level->addEntity(new Blood(level, pos, je::lengthdir((je::randomf(3) + 2) * (sin(timer / 10.f) + 1) / 2, 75 + rand() % 90), 2));
	sprite.setPosition(pos);
	if (sin(timer / 10.f) > 0)
		sprite.setTexture(out);
	else
		sprite.setTexture(in);
}

void Heart::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite);
}

}
