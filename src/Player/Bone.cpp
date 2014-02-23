#include "Player/Bone.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Assert.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Player/Player.hpp"
#include <iostream>
namespace con
{

Bone::Bone(je::Level *level, Player& owner, int length, int thickness, const std::string& filename)
	:je::Entity(level, "Bone", sf::Vector2f(0.f, 0.f), sf::Vector2i(length, thickness))
	,owner(owner)
	,parent(nullptr)
	,children()
	,limb(level->getGame().getTexManager().get(filename))
	,length(length)
	,thickness(thickness)
{
	//mBoneTransform.setOrigin(0.f, thickness / 2.f);
	mBoneTransform.setScale(1.f, 1.f);
}

void Bone::addChild(Bone *child)
{
	JE_ASSERT(child->parent == nullptr);
	child->parent = this;
	children.push_back(child);
}

sf::Transformable& Bone::boneTransform()
{
	return mBoneTransform;
}

const sf::Transformable& Bone::getBoneTransform() const
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
		this->updateBoneTransform(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), 0.f);
	}
}

void Bone::updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle)
{
	//	boneTransform() overrides anything done to the regular Enity transform
	pos += mBoneTransform.getPosition();
	if (parent)
		pos += je::lengthdir(scale.x * parent->length, -angle);
	scale.x *= mBoneTransform.getScale().x;
	scale.y *= mBoneTransform.getScale().y;
	origin += mBoneTransform.getOrigin();
	angle += mBoneTransform.getRotation();

	transform().setPosition(pos);
	transform().setScale(scale);
	transform().setOrigin(origin);
	transform().setRotation(angle);

	//std::cout << "(" << ((int)pos.x / 10) * 10 << ", " << ((int)pos.y / 10) * 10 << ")"
	//	<< " --  (" << scale.x << ", " << scale.x << ") -- asngle: " << angle << "\n";

	for (Bone *child : children)
		child->updateBoneTransform(pos, scale, origin, angle);
}

}