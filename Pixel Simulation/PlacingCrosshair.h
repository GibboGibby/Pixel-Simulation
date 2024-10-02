#pragma once
#include <raylib.h>
class PlacingCrosshair
{
public:
	void Update();
	void Render();

	Vector2 GetSize() { return size; }

	Vector2 size = {15,15};
};