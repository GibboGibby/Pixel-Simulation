#include "PlacingCrosshair.h"

void PlacingCrosshair::Update()
{
	Vector2 mosueWheel = GetMouseWheelMoveV();
	if (mosueWheel.y > 0)
	{
		float extraVal = 1.0f;
		if (IsKeyDown(KEY_LEFT_SHIFT)) extraVal = 3.0f;
		size = {size.x + (int)(2 * extraVal), size.y + (int)(2 * extraVal)};

	}
	if (mosueWheel.y < 0)
	{
		float extraVal = 1.0f;
		if (IsKeyDown(KEY_LEFT_SHIFT)) extraVal = 3.0f;
		size = {size.x - (int)(2 * extraVal), size.y - (int)(2 * extraVal)};
	}
}

void PlacingCrosshair::Render()
{
	Vector2 mousePos = GetMousePosition();
	Rectangle rect = { mousePos.x - size.x / 2, mousePos.y - size.y / 2, size.x, size.y };
	DrawRectangleLinesEx(rect, 2.0f, RED);
}
