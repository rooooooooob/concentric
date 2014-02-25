#include "Player/BoneAnimation.hpp"

#include "jam-engine/Utility/Assert.hpp"

#include "Player/Bone.hpp"
#include <iostream>
namespace con
{

BoneAnimation::BoneAnimation(TransformSet frame, unsigned int frameLength, bool repeat)
	:bones()
	,lengths(frame.transforms.size(), frameLength)
	,frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	bones.push_back(frame);
	this->transformBones();
}

BoneAnimation::BoneAnimation(std::initializer_list<TransformSet> frames, unsigned int frameLength, bool repeat)
	:bones()
	,lengths(frames.begin()->transforms.size(), frameLength)
	,frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	this->bones.reserve(bones.size());
	for (const TransformSet& bone : bones)
	{
		this->bones.push_back(bone);
		JE_ASSERT_MSG(bone.transforms.size() == this->bones.front().transforms.size(), "Bones in a single animation have varying animation lengths");
	}

	this->transformBones();
}

BoneAnimation::BoneAnimation(std::initializer_list<TransformSet> bones, std::initializer_list<unsigned int> lengths, bool repeat)
	:bones()
	,lengths()
	,frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	this->bones.reserve(bones.size());
	for (const TransformSet& bone : bones)
	{
		this->bones.push_back(bone);
		JE_ASSERT_MSG(bone.transforms.size() == lengths.size(), "Bones in a single animation have varying animation lengths or they dont match the frame lengths size");
	}
	this->lengths.reserve(lengths.size());
	for (unsigned int length : lengths)
	{
		this->lengths.push_back(length);
	}

	this->transformBones();
}


void BoneAnimation::addTransformSet(const TransformSet& set)
{
	bones.push_back(set);
	this->transformBones();
}

bool BoneAnimation::isFinished() const
{
	return !repeating && frame == lengths.size() - 1 && frameProgress >= lengths.back();
}

bool BoneAnimation::advanceFrame()
{
	//std::cout << "[ " << frameProgress <<  "/" << lengths[frame] << " ] -- ";
	if (++frameProgress >= lengths[frame])
	{
		if (frame < lengths.size() - 1)
		{
			frameProgress -= lengths[frame];
			++frame;
			this->transformBones();
			//std::cout << "[ " << frame + 1 <<  "/" << lengths.size() << " ]\n";
			return true;
		}
		else
		{
			if (repeating)
			{
				frameProgress -= lengths[frame];
				frame = 0;
			}
			else
			{
				frameProgress = lengths.back();
			}
		}
	}
	//std::cout << "[ " << frame + 1 <<  "/" << lengths.size() << " ]\n";
	return false;
}

void BoneAnimation::reset()
{
	frame = 0;
	this->transformBones();
}

void BoneAnimation::scaleRotations(float scalar)
{
	for (TransformSet& bone : bones)
	{
		sf::Transformable& transform = bone.bone->boneTransform();
		transform.setRotation(transform.getRotation() * scalar);
	}
}



/*			private			*/
void BoneAnimation::transformBones()
{
	for (TransformSet& bone : bones)
	{
		const BoneTransform& source = bone.transforms[frame];
		sf::Transformable& transform = bone.bone->boneTransform();
		transform.setPosition(source.pos);
		transform.setScale(source.scale);
		transform.setOrigin(source.origin);
		transform.setRotation(source.angle);

		//std::cout << "Bone::updateBoneTransfomr(angle(" << (int) (source.angle / 2) * 2 << "))" << std::endl;
	}
	//std::cout << std::endl;
}

}