#pragma once

#include <vector>
#include "CrossFadeTarget.h"
#include "Clip.h"
#include "Pose.h"
#include "Skeleton.h"

class CrossFadeController 
{
protected:
	std::vector<CrossFadeTarget> mTargets;
	Clip* mClip;
	float mTime;
	Pose mPose;
	Skeleton mSkeleton;
	bool mWasSkeletonSet;
	
public:
	CrossFadeController();
	CrossFadeController(Skeleton& skeleton);
	void SetSkeleton(Skeleton& skeleton);
	void Play(Clip* target);
	void FadeTo(Clip* target, float fadeTime);
	void Update(float dt);
	Pose& GetCurrentPose();
	Clip* GetcurrentClip();
};