#ifndef CON_BLOOD_HPP
#define CON_BLOOD_HPP

#include <cstdlib>
#include "Entity.hpp"

namespace con
{

class Blood : public je::Entity
{
public:
	Blood(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc, int type = rand() % 3);

	
private:
	void onUpdate() override;
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;



	sf::Sprite sprite;
	sf::Vector2f veloc;
	int timer;
};

}

#endif
