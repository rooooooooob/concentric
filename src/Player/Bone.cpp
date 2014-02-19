#include "Player/Bone.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Assert.hpp"

#include "Player/Player.hpp"

namespace con
{

Bone::Bone(je::Level *level, Player& owner, int length, int thickness, const std::string& filename)
	:je::Entity(level, "Bone", sf::Vector2f(0, 0), sf::Vector2i(length, thickness), sf::Vector2i(-(length>thickness?thickness:length)/2, -(length>thickness?thickness:length)/2))
	,owner(owner)
	,parent(nullptr)
	,children()
	,limb(level->getGame().getTexManager().get(filename))
{
}

void Bone::addChild(Bone *child)
{
	JE_ASSERT(child->parent == nullptr);
	child->parent = this;
	children.push_back(child);
}

sf::Transformable Bone::boneTransform()
{
	return mBoneTransform;
}

const sf::Transformable Bone::getBoneTransform() const
{
	return mBoneTransform;
}

/*		private			*/
void Bone::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates s = states;
	s.transform *= transform().getTransform();
	target.draw(limb, s);
}

void Bone::onUpdate()
{
	if (parent == nullptr)
	{
		//	no transform (at first) since no parent
		updateBoneTransform(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), 0.f);
	}
}

void Bone::updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle)
{
	//	boneTransform() overrides anything done to the regular Enity transform
	pos += mBoneTransform.getPosition();
	scale += mBoneTransform.getScale();
	origin += mBoneTransform.getOrigin();
	angle += mBoneTransform.getRotation();

	transform().setPosition(pos);
	transform().setScale(scale);
	transform().setOrigin(origin);
	transform().setRotation(angle);

	for (Bone *child : children)
		child->updateBoneTransform(pos, scale, origin, angle);
}

}