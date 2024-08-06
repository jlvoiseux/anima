#pragma once

#include "Game.h"
#include "../anim/Skeleton.h"
#include "../anim/Pose.h"
#include "../anim/Clip.h"
#include "../scene/Mesh.h"
#include "../render/Shader.h"
#include "../render/Texture.h"

enum SkinningMode {
	CPU,
	GPU
};

struct AnimationInstance {
	unsigned int mClip;
	float mTime;
	Pose mPose;
};

class Sample : public Game {
protected:
	Shader* mStaticShader;
	Shader* mSkinnedShader;
	Texture* mTexture;
	
	std::vector<Mesh> mMeshes;
	std::vector<Clip> mClips;
	Skeleton mSkeleton;
	Pose mPose;
	std::vector<mat4> mPosePalette;
	std::vector<mat4> mSkinPalette;

	AnimationInstance mA;
	AnimationInstance mB;
	float mBlendTime;
	bool mInvertBlend;

	SkinningMode mSkinningMode;
	
public:
	void Initialize();
	void ImGUI();
	void Update(float inDeltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
};