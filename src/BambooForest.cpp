#include "BambooForest.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

const int stalkHeight = 192;

namespace con
{

BambooForest::BambooForest(je::Level *level, const sf::Vector2f& pos, int width, float density)
	:je::Entity(level, "BambooForest", pos, sf::Vector2i(width, stalkHeight))
	,stalk(level->getGame().getTexManager().get("bamboo_stalk.png"))
	,trees()
{
	if (density > 0.f)
	{
		//	set origin at the bottom center
		stalk.setOrigin(2, stalkHeight);

		leaves[0].setTexture(level->getGame().getTexManager().get("bamboo_leaf0.png"));
		leaves[1].setTexture(level->getGame().getTexManager().get("bamboo_leaf1.png"));
		leaves[2].setTexture(level->getGame().getTexManager().get("bamboo_leaf2.png"));
		for (sf::Sprite& leaf : leaves)
		{
			leaf.setOrigin(5, 10);
		}
		//	add in a basic cover that's pretty much uniform
		for (int i = 0; i < width + 6; i += 6 / density)
		{
			trees.push_back(Tree(pos.x + i + je::random(3 / density), pos.y + 4 + je::random(8)));
		}
		//	now spawn a bunch totally at random
		const int n = je::random(density * width / 8);
		for (int i = 0; i < n; ++i)
		{
			trees.push_back(Tree(pos.x + je::random(width), pos.y + je::random(12)));
		}
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
	for (const Tree& tree : trees)
	{
		for (const Tree::Leaf& leaf : tree.leaves)
		{
			leaves[leaf.id].setPosition(tree.pos + je::lengthdir(leaf.height, -tree.angle + 90.f));
			leaves[leaf.id].setRotation(leaf.angle);
			target.draw(leaves[leaf.id], states);
		}
	}
}

/*		tree implementation			*/
BambooForest::Tree::Tree(int x, int y)
	:pos(x, y)
	,angle(-3.5f + je::randomf(7.f))
{
	for (int i = 2; i < sizeof(leaves) / sizeof(Leaf); ++i)
		leaves[i].height -= je::random(64);
}

BambooForest::Tree::Leaf::Leaf()
	:angle(135.f - je::randomf(270.f))
	,height(stalkHeight)
	,id(je::random(3))
{
}

}