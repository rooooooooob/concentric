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
	class BoneTransform
	{
	public:
		BoneTransform(float angle = 0.f, sf::Vector2f& scale = sf::Vector2f(1.f, 1.f), const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f), const sf::Vector2f& origin = sf::Vector2f(0.f, 0.f))
			:angle(angle)
			,scale(scale)
			,pos(pos)
			,origin(origin)
		{
		}

		//	transform data
		float angle;
		sf::Vector2f scale;
		sf::Vector2f pos;
		sf::Vector2f origin;
		
	};
	class TransformSet
	{
	public:
		TransformSet(Bone& bone, std::initializer_list<BoneTransform> transforms)
			:transforms()
			,bone(&bone)
		{
			this->transforms.reserve(transforms.size());
			for (const BoneTransform& transform : transforms)
				this->transforms.push_back(transform);
		}

		//	transforms to do at each frame
		std::vector<BoneTransform> transforms;
		//	bone to transform
		Bone *bone;
	};

	BoneAnimation(TransformSet frame, unsigned int frameLength, bool repeat = true);

	BoneAnimation(std::initializer_list<TransformSet> bones, unsigned int frameLength, bool repeat = true);

	BoneAnimation(std::initializer_list<TransformSet> bones, std::initializer_list<unsigned int> lengths, bool repeat = true);

	void addTransformSet(const TransformSet& set);


	bool isFinished() const;

	bool advanceFrame();

	void reset();


	void transformBones();

private:

	

	std::vector<TransformSet> bones;
	std::vector<unsigned int> lengths;
	unsigned int frameProgress;
	unsigned int frame;
	bool repeating;
};

}

#endif