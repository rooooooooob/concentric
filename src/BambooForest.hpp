#ifndef CON_BAMBOOFOREST_HPP
#define CON_BAMBOOFOREST_HPP

#include "Entity.hpp"

namespace con
{

class BambooForest : public je::Entity
{
public:
	BambooForest(je::Level *level, const sf::Vector2f& pos, int width);

private:
	class Tree
	{
	public:
		Tree(int x, int y);

		sf::Vector2f pos;
		float angle;
	};

	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;


	mutable sf::Sprite stalk;
	std::vector<Tree> trees;
};

}

#endif