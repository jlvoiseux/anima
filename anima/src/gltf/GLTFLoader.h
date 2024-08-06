#pragma once

#include "../anim/Clip.h"
#include "../anim/Pose.h"
#include "../anim/Skeleton.h"
#include "cgltf.h"

cgltf_data* LoadGLTFFile(const char* path);
void FreeGLTFFile(cgltf_data* handle);
Pose LoadRestPose(cgltf_data* data);

std::vector<std::string> LoadJointNames(cgltf_data* data);
std::vector<Clip> LoadAnimationClips(cgltf_data* data);
Pose LoadBindPose(cgltf_data* data);
Skeleton LoadSkeleton(cgltf_data* data);
std::vector<Mesh> LoadMeshes(cgltf_data* data);
