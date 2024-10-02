#pragma once
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 100.0f

struct Vec2
{
	int x;
	int y;
	Vec2(int _x = 0, int _y = 0) : x(_x), y(_y) {}

	float MagnitudeSquared() {
		return x * x + y * y;
	}

	float Magnitude() {
		return (float)sqrt(MagnitudeSquared());
	}

	Vec2 Normalized() {
		float mag = Magnitude();

		return Vec2(x / mag, y / mag);
	}
	float DotProduct(Vec2 a, Vec2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
	float Cross(Vec2 a, Vec2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	Vec2& operator +=(const Vec2& right)
	{
		x += right.x;
		y += right.y;

		return *this;
	}

	Vec2& operator -=(const Vec2& right)
	{
		x -= right.x;
		y -= right.y;

		return *this;
	}
};

inline float Dot(Vec2 a, Vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

inline float Cross(Vec2 a, Vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

inline Vec2 Cross(Vec2 a, float s)
{
	return Vec2(s * a.y, -s * a.x);
}
inline Vec2 Cross(float s, Vec2 a)
{
	return Vec2(-s * a.y, s * a.x);
}

inline Vec2 operator +(const Vec2& left, const Vec2& right)
{
	return Vec2(left.x + right.x, left.y + right.y);
}

inline Vec2 operator +(const Vec2& left, const float& right)
{
	return Vec2(left.x + right, left.y + right);
}

inline Vec2 operator -(const Vec2& left, const Vec2& right)
{
	return Vec2(left.x - right.x, left.y - right.y);
}
inline Vec2 operator -(const Vec2& left, const float& right)
{
	return Vec2(left.x - right, left.y - right);
}

inline Vec2 operator -(const Vec2& right)
{
	return Vec2(-right.x, -right.y);
}

inline Vec2 operator *(const Vec2& left, const float right)
{
	return Vec2(left.x * right, left.y * right);
}

inline Vec2 operator * (const float& left, const Vec2& right)
{
	return Vec2(left * right.x, left * right.y);
}

inline Vec2 operator /(const Vec2& left, const float right)
{
	return Vec2(left.x / right, left.y / right);
}

inline Vec2 operator / (const float& left, const Vec2& right)
{
	return Vec2(left / right.x, left / right.y);
}

inline Vec2 RotateVector(Vec2& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vec2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}



const Vec2 VEC2_ZERO = { 0,0 };
const Vec2 VEC2_ONE = { 1,1 };
const Vec2 VEC2_UP = { 0,-1 };
const Vec2 VEC2_RIGHT = { 1,0 };
