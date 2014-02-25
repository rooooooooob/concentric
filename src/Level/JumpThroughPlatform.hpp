#ifndef CON_JUMP_THROUGH_PLATFORM_HPP
#define CON_JUMP_THROUGH_PLATFORM_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace con
{

class JumpThroughPlatform : public je::Entity
{
public:
	JumpThroughPlatform(je::Level *level, const sf::Vector2f& pos);

	JumpThroughPlatform(je::Level *level, int x, int y, sf::Rect<int> bounds, const std::string& fname);

	/**
	 * Checks if the platform should behave as solid for the input Entity
	 * @param entity The Entity to check whether this should behave as solid or not for
	 * @return Whether or not to count this platform as solid
	 */
	bool isSolid(const je::Entity& entity) const;

private:

	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;



	sf::Sprite sprite;
};

}

#endif // CON_JUMP_THROUGH_PLATFORM_HPP
