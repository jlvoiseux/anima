#include <iostream>
#include "Sample.h"
#include "../gltf/GLTFLoader.h"
#include "../anim/Blending.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../render/Uniform.h"
#include "../profiling/tracy/Tracy.hpp"

void Sample::Initialize() {
	cgltf_data* gltf = LoadGLTFFile("assets/models/magic.glb");
	mSkeleton = LoadSkeleton(gltf);
	mClips = LoadAnimationClips(gltf);
	mMeshes = LoadMeshes(gltf);
	FreeGLTFFile(gltf);

	mPose = mSkeleton.GetRestPose();
	mPose.GetMatrixPalette(mPosePalette);
	mSkinPalette = mSkeleton.GetInvBindPose();

	mStaticShader = new Shader("assets/shaders/static.vert", "assets/shaders/lit.frag");
	mSkinnedShader = new Shader("assets/shaders/skinned.vert", "assets/shaders/lit.frag");
	mTexture = new Texture("assets/models/colors.png");

	mA.mPose = mPose;
	mB.mPose = mPose;

	mBlendTime = 0.0f;
	mInvertBlend = false;

	mA.mClip = 0;
	mB.mClip = 1;
	for (unsigned int i = 0, size = (unsigned int)mClips.size(); i < size; ++i) {
		if (mClips[i].GetName() == "Gangnam") {
			mA.mClip = i;
			mA.mTime = mClips[i].GetStartTime();
		}
		else if (mClips[i].GetName() == "HipHop") {
			mB.mClip = i;
			mB.mTime = mClips[i].GetStartTime();
		}
	}

	mSkinningMode = SkinningMode::GPU;
}

void Sample::ImGUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Animation System");
	if (ImGui::BeginCombo("Skinning Mode", mSkinningMode == SkinningMode::CPU ? "CPU" : "GPU"))
	{
		for (unsigned int i = 0, size = (unsigned int)mMeshes.size(); i < size; ++i) {
			mMeshes[i].UpdateOpenGLBuffers();
		}
		
		if (ImGui::Selectable("CPU", mSkinningMode == SkinningMode::CPU))
		{
			mSkinningMode = SkinningMode::CPU;
		}
		if (ImGui::Selectable("GPU", mSkinningMode == SkinningMode::GPU))
		{
			mSkinningMode = SkinningMode::GPU;
		}
		ImGui::EndCombo();
	}
	ImGui::SliderFloat("Blend coefficient", &mBlendTime, 0.0f, 1.0f);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Sample::Update(float dt) {
	ZoneScoped;
	mA.mTime = mClips[mA.mClip].Sample(mA.mPose, mA.mTime + dt);
	mB.mTime = mClips[mB.mClip].Sample(mB.mPose, mB.mTime + dt);

	Blend(mPose, mA.mPose, mB.mPose, mBlendTime, -1);

	switch (mSkinningMode)
	{
	case SkinningMode::CPU:
		for (unsigned int i = 0, size = (unsigned int)mMeshes.size(); i < size; ++i) {
			mMeshes[i].CPUSkin(mSkeleton, mPose);
		}
		break;
	case SkinningMode::GPU:
	default:
		mPose.GetMatrixPalette(mPosePalette);
		break;
	}
}

void Sample::Render(float aspect) {
	ZoneScoped;
	
	Shader* vertShader;
	
	switch (mSkinningMode)
	{
	case SkinningMode::CPU:
		vertShader = mStaticShader;
		break;
	case SkinningMode::GPU:
	default:
		vertShader = mSkinnedShader;
		break;
	}
	
	mat4 model;
	mat4 view = lookAt(vec3(0, 3, 5), vec3(0, 3, 0), vec3(0, 1, 0));
	mat4 projection = perspective(60.0f, aspect, 0.01f, 1000.0f);
	
	vertShader->Bind();
	Uniform<mat4>::Set(vertShader->GetUniform("model"), model);
	Uniform<mat4>::Set(vertShader->GetUniform("view"), view);
	Uniform<mat4>::Set(vertShader->GetUniform("projection"), projection);
	if (mSkinningMode == SkinningMode::GPU)
	{
		Uniform<mat4>::Set(vertShader->GetUniform("pose"), mPosePalette);
		Uniform<mat4>::Set(vertShader->GetUniform("invBindPose"), mSkinPalette);
	}
	Uniform<vec3>::Set(vertShader->GetUniform("light"), vec3(1, 1, 1));
	mTexture->Set(vertShader->GetUniform("tex0"), 0);
	
	for (unsigned int i = 0, size = (unsigned int)mMeshes.size(); i < size; ++i) {
		switch (mSkinningMode)
		{
		case SkinningMode::CPU:
			mMeshes[i].Bind(vertShader->GetAttribute("position"), vertShader->GetAttribute("normal"), vertShader->GetAttribute("texCoord"), -1, -1);
			mMeshes[i].Draw();
			mMeshes[i].UnBind(vertShader->GetAttribute("position"), vertShader->GetAttribute("normal"), vertShader->GetAttribute("texCoord"), -1, -1);
			break;
		case SkinningMode::GPU:
			mMeshes[i].Bind(vertShader->GetAttribute("position"), vertShader->GetAttribute("normal"), vertShader->GetAttribute("texCoord"), vertShader->GetAttribute("weights"), vertShader->GetAttribute("joints"));
			mMeshes[i].Draw();
			mMeshes[i].UnBind(vertShader->GetAttribute("position"), vertShader->GetAttribute("normal"), vertShader->GetAttribute("texCoord"), vertShader->GetAttribute("weights"), vertShader->GetAttribute("joints"));
			break;
		}
	}
	mTexture->UnSet(0);

	vertShader->UnBind();
}

void Sample::Shutdown() {
	mClips.clear();
	mMeshes.clear();
	delete mStaticShader;
	delete mSkinnedShader;
	delete mTexture;
}