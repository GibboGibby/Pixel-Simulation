#pragma once
#include "Pixel.h"
#include <array>

struct PixelSerialized
{
	PixelType type = AIR;
	unsigned char variant = 0;
};