#pragma once

#include <vector>
#include "../anim/Pose.h"
#include "../render/Shader.h"
#include "../render/Attribute.h"
#include "../linalg/vec3.h"
#include "../linalg/mat4.h"

enum class DebugDrawMode 
{
	Lines, Loop, Strip, Points
};

class DebugDraw 
{
protected:
	std::vector<vec3> mPoints;
	Attribute<vec3>* mAttribs;
	Shader* mShader;
	
private:
	DebugDraw(const DebugDraw&);
	DebugDraw& operator=(const DebugDraw&);
	
public:
	DebugDraw();
	DebugDraw(unsigned int size);
	~DebugDraw();

	unsigned int Size();
	void Resize(unsigned int newSize);
	vec3& operator[](unsigned int index);
	void Push(const vec3& v);

	void FromPose(Pose& pose);

	void UpdateOpenGLBuffers();
	void Draw(DebugDrawMode mode, const vec3& color, const mat4& mvp);
};
