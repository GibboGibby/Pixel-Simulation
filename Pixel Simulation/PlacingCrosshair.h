#pragma once
#include <raylib.h>
class PlacingCrosshair
{
public:
	void Update();
	void Render();

	Vector2 GetSize() { return size; }
	void DisableCrosshair();
	void EnableCrosshair();
	bool IsEnabled() { return disabled; }
	
private:
	bool disabled = false;
	Vector2 size = {15,15};
};