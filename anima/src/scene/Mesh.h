#pragma once

#include <vector>
#include "../linalg/mat4.h"
#include "../linalg/vec2.h"
#include "../linalg/vec3.h"
#include "../linalg/vec4.h"
#include "../render/Attribute.h"
#include "../render/IndexBuffer.h"
#include "../anim/Pose.h"
#include "../anim/Skeleton.h"

class Mesh 
{
protected:
	std::vector<vec3> mPosition;
	std::vector<vec3> mNormal;
	std::vector<vec2> mTexCoord;
	std::vector<vec4> mWeights;
	std::vector<ivec4> mInfluences;
	std::vector<unsigned int> mIndices;

	Attribute<vec3>* mPosAttrib;
	Attribute<vec3>* mNormAttrib;
	Attribute<vec2>* mUvAttrib;
	Attribute<vec4>* mWeightAttrib;
	Attribute<ivec4>* mInfluenceAttrib;
	IndexBuffer* mIndexBuffer;

	std::vector<vec3> mSkinnedPosition;
	std::vector<vec3> mSkinnedNormal;
	std::vector<mat4> mPosePalette;

public:
	Mesh();
	Mesh(const Mesh&);
	Mesh& operator=(const Mesh&);
	~Mesh();

	std::vector<vec3>& GetPosition();
	std::vector<vec3>& GetNormal();
	std::vector<vec2>& GetTexCoord();
	std::vector<vec4>& GetWeights();
	std::vector<ivec4>& GetInfluences();
	std::vector<unsigned int>& GetIndices();

	void CPUSkin(Skeleton& skeleton, Pose& pose);
	void UpdateOpenGLBuffers();
	void Bind(int position, int normal, int texCoord, int weight, int influence);

	void Draw();
	void DrawInstanced(unsigned int numInstances);
	void UnBind(int position, int normal, int texCoord, int weight, int influence);
};