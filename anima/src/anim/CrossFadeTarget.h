#pragma once

#include "Clip.h"
#include "Pose.h"

struct CrossFadeTarget 
{
	Pose mPose;
	Clip* mClip;
	float mTime;
	float mDuration;
	float mElapsed;
	inline CrossFadeTarget() : 
		mClip(0), mTime(0.0f), mDuration(0.0f), mElapsed(0.0f) { }
	inline CrossFadeTarget(Clip* target, Pose& pose, float dur) : 
		mClip(target), mTime(target->GetStartTime()), mPose(pose), mDuration(dur), mElapsed(0.0f) { }
};