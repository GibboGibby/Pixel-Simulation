#pragma once
#include "raylib.h"
#include <cstdlib>

enum PixelType : char
{
	AIR,
	WOOD,
	SAND,
	WATER,

	PIXEL_COUNT
};

 

struct Pixel 
{
	Pixel() = default;
	Pixel(PixelType _type) {
		type = _type;
		variant = (char)(rand() % 256);
	}
	PixelType type;
	unsigned char variant;
	bool hasUpdated = false;


	Color GetColor()
	{
		switch (type)
		{
		case AIR:
			return { 0,0,0,255 };
			break;
		case WOOD:
			break;
		case SAND:
			break;
		case WATER:
			break;
		default:
			return { 0,0,0,255 };
			break;
		}
	}

};