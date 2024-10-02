#pragma once
#include "raylib.h"
#include <cstdlib>
#include <map>
#include <iostream>

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

};

inline bool CheckFlag(int flags)
{
	return false;
}

 

struct Pixel 
{
	Pixel() = default;
	Pixel(PixelType _type) {
		type = _type;
		variant = (unsigned char)(rand() % 256);
	}
	PixelType type;
	unsigned char variant;
	bool hasUpdated = false;


	Color GetColor()
	{
		switch (type)
		{
		case AIR:
			return { 0,0,0,0 };
			break;
		case WOOD:
			return { 150,75,0,255 };
			break;
		case SAND:
			return { 255, 255, 0, 255 };
			break;
		case WATER:
			return { 0,0,255,255 };
			break;
		default:
			return { 0,0,0,0 };
			break;
		}
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
	// Type,
	{UNDEFINED, {"Undefined"}},
	{VOID, {"Void"}}
};