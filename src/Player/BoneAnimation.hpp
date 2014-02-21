#ifndef CON_BONE_ANIMATION_HPP
#define CON_BONE_ANIMATION_HPP

#include <initializer_list>
#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

namespace con
{

class Bone;

class BoneAnimation
{
public:
	struct BoneTransform
	{
		//	transform data
		sf::Vector2f pos;
		sf::Vector2f scale;
		sf::Vector2f origin;
		float angle;
	};
	struct TransformSet
	{
		//	transforms to do at each frame
		std::vector<BoneTransform> transforms;
		//	bone to transform
		Bone& bone;
	};


	BoneAnimation(std::initializer_list<TransformSet> bones, unsigned int frameLength, bool repeat = true);

	BoneAnimation(std::initializer_list<TransformSet> bones, std::initializer_list<unsigned int> lengths, bool repeat = true);

	bool isFinished() const;

	bool advanceFrame();

	void reset();




private:

	void transformBones();

	std::vector<TransformSet> bones;
	std::vector<unsigned int> lengths;
	unsigned int frameProgress;
	unsigned int frame;
	bool repeating;
};

}

#endif