#ifndef CON_SOLIDGROUND_HPP
#define CON_SOLIDGROUND_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "Entity.hpp"

namespace con
{

class SolidGround : public je::Entity
{
public:
	SolidGround(je::Level *level, int x, int y, sf::Rect<int> bounds, const std::string& fname);


private:

	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;



	sf::Sprite sprite;
};

}

#endif // CON_SOLIDGROUND_HPP
