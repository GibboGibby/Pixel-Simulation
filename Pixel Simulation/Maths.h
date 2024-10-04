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


// HSV STUFF

union Vec3U8
{
	struct
	{
		uint8_t x;
		uint8_t y;
		uint8_t z;
	};

	struct
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	struct
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};

	uint8_t elements[3];
	uint8_t v[3];
};

inline Vec3U8 HsvToRgb(Vec3U8 hsv)
{
	Vec3U8 rgb;
	unsigned char region, remainder, p, q, t;

	if (hsv.y == 0)
	{
		rgb.r = hsv.z;
		rgb.g = hsv.z;
		rgb.b = hsv.z;
		return rgb;
	}

	region = hsv.x / 43;
	remainder = (hsv.x - (region * 43)) * 6;

	p = (hsv.z * (255 - hsv.y)) >> 8;
	q = (hsv.z * (255 - ((hsv.y * remainder) >> 8))) >> 8;
	t = (hsv.z * (255 - ((hsv.y * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
	case 0:
		rgb.r = hsv.z; rgb.g = t; rgb.b = p;
		break;
	case 1:
		rgb.r = q; rgb.g = hsv.z; rgb.b = p;
		break;
	case 2:
		rgb.r = p; rgb.g = hsv.z; rgb.b = t;
		break;
	case 3:
		rgb.r = p; rgb.g = q; rgb.b = hsv.z;
		break;
	case 4:
		rgb.r = t; rgb.g = p; rgb.b = hsv.z;
		break;
	default:
		rgb.r = hsv.z; rgb.g = p; rgb.b = q;
		break;
	}

	return rgb;
}

inline Vec3U8 RgbToHsv(Vec3U8 rgb)
{
	Vec3U8 hsv;
	unsigned char rgbMin, rgbMax;

	rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
	rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

	hsv.z = rgbMax;
	if (hsv.z == 0)
	{
		hsv.x = 0;
		hsv.y = 0;
		return hsv;
	}

	hsv.y = 255 * (long)(rgbMax - rgbMin) / hsv.z;
	if (hsv.y == 0)
	{
		hsv.x = 0;
		return hsv;
	}

	if (rgbMax == rgb.r)
		hsv.x = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
	else if (rgbMax == rgb.g)
		hsv.x = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
	else
		hsv.x = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

	return hsv;
}

inline float Max(float a, float b)
{
	//if (a > b) return b
}

inline float Min(float a, float b)
{
	return (a > b) ? b : a;
}