#ifndef CON_HEAD_HPP
#define CON_HEAD_HPP

#include "Entity.hpp"
#include "Player.hpp"

namespace con
{

class Head : public je::Entity
{
public:
	Head(je::Level *level, int x, int y, Player& owner);

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;

	Player& owner;
	sf::Sprite sprite;
};

}

#endif // CON_HEAD_HPP
