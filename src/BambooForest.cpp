#include "BambooForest.hpp"

#include "Game.hpp"
#include "Level.hpp"
#include "Random.hpp"

namespace con
{

BambooForest::BambooForest(je::Level *level, const sf::Vector2f& pos, int width)
	:je::Entity(level, "BambooForest", pos, sf::Vector2i(width, 128))
	,stalk(level->getGame().getTexManager().get("bamboo_stalk.png"))
	,trees()
{
	//	set origin at the bottom center
	stalk.setOrigin(2, 128);
	//	add in a basic cover that's pretty much uniform
	for (int i = 0; i < width; i += 4)
	{
		trees.push_back(Tree(pos.x + i + je::random(3), pos.y + 2 + je::random(4)));
	}
	//	now spawn a bunch totally at random
	const int n = je::random(width / 16);
	for (int i = 0; i < n; ++i)
	{
		trees.push_back(Tree(pos.x + je::random(width), pos.y + je::random(6)));
	}
	this->setDepth(1000);
}

void BambooForest::onUpdate()
{
}

void BambooForest::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	for (const Tree& tree : trees)
	{
		stalk.setPosition(tree.pos);
		stalk.setRotation(tree.angle);
		target.draw(stalk, states);
	}
}

/*		tree implementation			*/
BambooForest::Tree::Tree(int x, int y)
	:pos(x, y)
	,angle(-5 + je::random(10))
{
}

}