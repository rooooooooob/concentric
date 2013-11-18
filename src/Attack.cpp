#include "Attack.hpp"

namespace con
{

Attack::Attack(je::Level *level, const sf::Vector2f *follow, const sf::Vector2f& cpos, const sf::Vector2i& dim, int team, int time, float damage, const sf::Vector2f& veloc)
    :je::Entity(level, "Attack", cpos, dim)
    ,follow(follow)
    ,cpos(cpos)
    ,veloc(veloc)
    ,team(team)
    ,time(time)
    ,damage(damage)
{
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

int Attack::getTeam() const
{
    return team;
}

}
