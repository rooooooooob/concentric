#include "Attack.hpp"

namespace con
{

Attack::Attack(je::Level *level, const sf::Vector2f *follow, const sf::Vector2f& cpos, const sf::Vector2i& dim, const PlayerConfig& config, int time, float damage, const sf::Vector2f& veloc)
    :je::Entity(level, "Attack", cpos, dim)
    ,follow(follow)
    ,cpos(cpos)
    ,veloc(veloc)
    ,config(config)
    ,time(time)
    ,damage(damage)
{
}

const PlayerConfig& Attack::getPlayerConfig() const
{
	return config;
}

void Attack::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

void Attack::onUpdate()
{
    if (--time < 0)
        this->destroy();
    if (follow)
    {
        cpos += veloc;
        pos = *follow + cpos;
    }
    else
        pos += veloc;
}

float Attack::getDamage() const
{
    return damage;
}

}
