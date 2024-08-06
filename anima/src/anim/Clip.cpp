#pragma once

#include "Clip.h"

Clip::Clip() 
{
	mName = "No name given";
	mStartTime = 0.0f;
	mEndTime = 0.0f;
	mLooping = true;
}

float Clip::Sample(Pose& outPose, float time) 
{
	if (GetDuration() == 0.0f) 
	{
		return 0.0f;
	}
	
	time = AdjustTimeToFitRange(time);
	size_t size = mTracks.size();
	for (unsigned int i = 0; i < size; ++i) 
	{
		unsigned int j = mTracks[i].GetId(); // Joint
		Transform local = outPose.GetLocalTransform(j);
		Transform animated = mTracks[i].Sample(local, time, mLooping);
		outPose.SetLocalTransform(j, animated);
	}
	
	return time;
}

float Clip::AdjustTimeToFitRange(float inTime)
{
	if (mLooping) 
	{
		float duration = mEndTime - mStartTime;
		if (duration <= 0) { 0.0f; }
		
		inTime = fmodf(inTime - mStartTime, mEndTime - mStartTime);
		if (inTime < 0.0f) 
		{
			inTime += mEndTime - mStartTime;
		}
		inTime = inTime + mStartTime;
	}
	else
	{
		if (inTime < mStartTime) 
		{
			inTime = mStartTime;
		}
		if (inTime > mEndTime) 
		{
			inTime = mEndTime;
		}
	}
	
	return inTime;
}

void Clip::RecalculateDuration() 
{
	mStartTime = 0.0f;
	mEndTime = 0.0f;
	bool startSet = false;
	bool endSet = false;
	size_t tracksSize = mTracks.size();
	for (size_t i = 0; i < tracksSize; ++i)
	{
		if (mTracks[i].IsValid()) 
		{
			float startTime = mTracks[i].GetStartTime();
			float endTime = mTracks[i].GetEndTime();
			if (startTime < mStartTime || !startSet) 
			{
				mStartTime = startTime;
				startSet = true;
			}
			
			if (endTime > mEndTime || !endSet) 
			{
				mEndTime = endTime;
				endSet = true;
			}
		}
	}
}

TransformTrack& Clip::operator[](unsigned int joint) 
{
	for (size_t i = 0, s = mTracks.size(); i < s; ++i) 
	{
		if (mTracks[i].GetId() == joint) 
		{
			return mTracks[i];
		}
	}
	
	mTracks.push_back(TransformTrack());
	mTracks[mTracks.size() - 1].SetId(joint);
	return mTracks[mTracks.size() - 1];
}

std::string& Clip::GetName() 
{
	return mName;
}

unsigned int Clip::GetIdAtIndex(unsigned int index) 
{
	return mTracks[index].GetId();
}

unsigned int Clip::Size() 
{
	return (unsigned int)mTracks.size();
}

float Clip::GetDuration() 
{
	return mEndTime - mStartTime;
}

float Clip::GetStartTime() 
{
	return mStartTime;
}

float Clip::GetEndTime() 
{
	return mEndTime;
}

bool Clip::GetLooping() 
{
	return mLooping;
}

void Clip::SetName(const std::string& inNewName) 
{
	mName = inNewName;
}

void Clip::SetIdAtIndex(unsigned int index, unsigned int id) 
{
	return mTracks[index].SetId(id);
}

void Clip::SetLooping(bool inLooping) 
{
	mLooping = inLooping;
}