#pragma once

#include "../linalg/Transform.h"
#include "Track.h"

class TransformTrack 
{
	
protected:
	unsigned int mId;
	VectorTrack mPosition;
	QuaternionTrack mRotation;
	VectorTrack mScale;
	
public:
	TransformTrack();
	unsigned int GetId();
	void SetId(unsigned int id);
	VectorTrack& GetPositionTrack();
	QuaternionTrack& GetRotationTrack();
	VectorTrack& GetScaleTrack();
	float GetStartTime();
	float GetEndTime();
	bool IsValid();
	Transform Sample(const Transform& ref, float time, bool looping);
};