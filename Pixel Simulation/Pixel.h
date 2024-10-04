#pragma once
#define Clamp(a, x, b) (((a)>(x))?(a):((b)<(x))?(b):(x))

#include "raylib.h"
#include <cstdlib>
#include <map>
#include <iostream>
#include "Maths.h"

enum PixelType : char
{
	AIR,
	WOOD,
	SAND,
	WATER,

	PIXEL_COUNT,
	UNDEFINED,
	VOID
};

enum PixelFlags
{
	MOVE_X,
	MOVE_Y,
	MOVE_DIAG,
	FALL,
	RISE
};
 
const bool SAND_WITH_TINTING = false;

struct alignas(64) Pixel 
{
	Pixel() = default;
	Pixel(PixelType _type) {
		type = _type;
		variant = (unsigned char)(rand() % 256);
		if (type == WOOD) isResting = true;
	}
	PixelType type;
	unsigned char variant;
	bool hasUpdated = false;
	Vector2 vel = {0.0f,0.0f};
	bool isResting = false;
	bool hasCollided;
	int lifeRemaining;



	
	Color GetColor()
	{
		Color baseCol;
		uint32_t noise = -10 + variant % 20;
		switch (type)
		{
		case AIR:
			return { 0,0,0,0 };
			break;
		case WOOD:
			baseCol = { 161,106,82,255 };
			noise /= 2;
			break;
		case SAND:
			//baseCol = { 242,216,145,255 };
			//baseCol = { 242,216,192,255 };
			baseCol = { 242, 228, 168, 255 };
			break;
		case WATER:
			baseCol = { 74, 147, 244, 170 };
			break;
		default:
			return { 0,0,0,0 };
			break;
		}
		// Tinting
		if (SAND_WITH_TINTING)
		{
			Vec3U8 temp_col = RgbToHsv({ baseCol.r, baseCol.g, baseCol.b });
			temp_col.y /= 2;
			temp_col = HsvToRgb(temp_col);
			baseCol.r = temp_col.r;
			baseCol.g = temp_col.g;
			baseCol.b = temp_col.b;
		}
		
		

		// Adding noise
		baseCol.r += noise;
		baseCol.g += noise;
		baseCol.b += noise;
		baseCol.r = Clamp(0, baseCol.r, 255);
		baseCol.g = Clamp(0, baseCol.g, 255);
		baseCol.b = Clamp(0, baseCol.b, 255);
		return baseCol;
	}
	

	void SetRandomVariant()
	{
		variant = (unsigned char)(rand() % 256);
	}

};

struct PixelData
{
	char name[128];
	bool move_x;
	bool move_y;
	bool move_diag;
	bool fall;
	bool rise;
	bool y_to_x_splat;
	bool spread;
	bool limited_life;
	bool death_spawn;
	bool rest_integrity;
	bool touch_destroy;
	float accel;
	float max_speed;
	uint16_t start_life;
	float friction;
	PixelType death_pixel_type;
	PixelType spread_to;
};

const std::map<PixelType, PixelData> PixelDataTable
{
	// COPY PIXEL DATA FROM RANDY AS I AM LAZY LMAO
	// Type,	    Name,		MoveX	MoveY	MoveDiag	Fall	Rise	Y2X		Spread	LimLife	 
	{UNDEFINED, {"Undefined",	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.f, 0.f, 0, 0.f, UNDEFINED, UNDEFINED}},
	{VOID,		{"Void",		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0.f, 0.f, 0, 0.f, UNDEFINED, UNDEFINED}},
	{AIR,		{"Air",			 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.f, 0.f, 0, 0.f, UNDEFINED, UNDEFINED}},
	{WATER,		{"Water",		 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0.4f, 10.f, 0, 0.f, UNDEFINED, UNDEFINED}},
	{SAND,		{"Sand",		 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 9.8f, 10.f, 0, 0.2f, UNDEFINED, UNDEFINED}},
	{WOOD,		{"Wood",		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.f, 0.f, 0, 0.f, UNDEFINED, UNDEFINED}}
};

inline bool CheckFlag(Pixel* pixel, PixelFlags flag)
{
	const PixelData* data = &PixelDataTable.at(pixel->type);
	switch (flag)
	{
	case MOVE_X:
		return data->move_x;
		break;
	case MOVE_Y:
		return data->move_y;
		break;
	case MOVE_DIAG:
		return data->move_diag;
		break;
	case FALL:
		return data->fall;
	case RISE:
		return data->rise;
	default:
		return false;
		break;
	}
	return false;
}