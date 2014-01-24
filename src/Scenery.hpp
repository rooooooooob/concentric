#ifndef CON_SCENERY_HPP
#define CON_SCENERY_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "Core/Entity.hpp"

namespace con
{

class Scenery : public je::Entity
{
public:
	Scenery(je::Level *level, int x, int y, const std::string& fname);


private:

	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;



	sf::Sprite sprite;
};

}

#endif
