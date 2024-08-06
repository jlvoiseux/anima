#pragma once

#define QUAT_EPSILON 0.000001f

#include "vec3.h"
#include "mat4.h"

struct quat 
{
    union 
    {
        struct 
        {
            float x;
            float y;
            float z;
            float w;
        };
        struct 
        {
            vec3 vector;
            float scalar;
        };
        float v[4];
    };
    
    inline quat() : x(0), y(0), z(0), w(1) { }
    inline quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

bool operator==(const quat& left, const quat& right);
bool operator!=(const quat& a, const quat& b);
quat operator+(const quat& a, const quat& b);
quat operator-(const quat& q);
quat operator-(const quat& a, const quat& b);
quat operator*(const quat& a, float b);
vec3 operator*(const quat& q, const vec3& v);
quat operator*(const quat& Q1, const quat& Q2);
quat operator^(const quat& q, float f);
quat angleAxis(float angle, const vec3& axis);
quat fromTo(const vec3& from, const vec3& to);
vec3 getAxis(const quat& quat);
float getAngle(const quat& quat);
bool sameOrientation(const quat& left, const quat& right);
float dot(const quat& a, const quat& b);
float lenSq(const quat& q);
float len(const quat& q);
void normalize(quat& q);
quat normalized(const quat& q);
quat conjugate(const quat& q);
quat inverse(const quat& q);
quat mix(const quat& from, const quat& to, float t);
quat nlerp(const quat& from, const quat& to, float t);
quat slerp(const quat& start, const quat& end, float t);
quat lookRotation(const vec3& direcion, const vec3& up);
mat4 quatToMat4(const quat& q);
quat mat4ToQuat(const mat4& m);