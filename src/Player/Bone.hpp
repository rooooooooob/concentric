#ifndef CON_BONE_HPP
#define CON_BONE_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace con
{

class Player;

class Bone : public je::Entity
{
public:
	Bone(je::Level *level, Player& owner, int length, int thickness, const std::string& filename);

	void addChild(Bone *child);

	sf::Transformable& boneTransform();

	const sf::Transformable& getBoneTransform() const;

private:

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;

	void updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle);


	Player& owner;
	Bone *parent;
	std::vector<Bone*> children; // non-owning since Bone is an Entity
	sf::Sprite limb;
	//sf::Sprite connector; TODO: implement this you faglord
	sf::Transformable mBoneTransform;
	int length;
	int thickness;
};

}

#endif