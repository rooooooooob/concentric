#include "Player/Heart.hpp"

#include <cmath>
#include "Player/Blood.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Trig.hpp"
#include "jam-engine/Utility/Random.hpp"

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
		transform().move(veloc);
		sprite.rotate(0.1);
	}
	if (getPos().x < -32 || getPos().x > level->getWidth() + 32)
		this->destroy();
	level->addEntity(new Blood(level, getPos(), je::lengthdir((je::randomf(3) + 2) * (sin(timer / 10.f) + 1) / 2, 75 + rand() % 90), 2));
	sprite.setPosition(getPos());
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
