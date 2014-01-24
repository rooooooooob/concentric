#ifndef CON_HEART_HPP
#define CON_HEART_HPP

#include "Core/Entity.hpp"

namespace con
{

class Heart : public je::Entity
{
public:
	Heart(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc);

private:
	void onUpdate() override;
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;


	const sf::Texture& in;
	const sf::Texture& out;
	sf::Sprite sprite;
	int timer;
	sf::Vector2f veloc;
};

}

#endif
