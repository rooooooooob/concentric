#ifndef CON_GRAPPLINGHOOK_HPP
#define CON_GRAPPLINGHOOK_HPP

#include <SFML/Graphics/Vertex.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace con
{

class Player;

class GrapplingHook : public je::Entity
{
public:
	GrapplingHook(Player& player, const sf::Vector2f& pos, const sf::Vector2f& velocity);

	/**
	 * Pulls the hook toward the player
	 * @return true if the hook has fully retracted, false otherwise
	 */
	bool pullIn();


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;


	Player& player;
	sf::Vector2f velocity;
	sf::Vertex line[2];
	sf::Sprite hookSprite;
	float gravity;
	bool stuck;
};

} // con

#endif // CON_GRAPPLINGHOOK_HPP