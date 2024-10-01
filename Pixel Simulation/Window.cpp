#include "Window.h"

void Window::Init(int width, int height, const char* stringName)
{
	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	InitWindow(1920, 1080, "Pixel Simulation");
	/*
	SetFPSTarget(144);
	SetState(FLAG_WINDOW_HIGHDPI);
	SetFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
	SetFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetWindowExitKey(KEY_GRAVE);
	SetTraceLevel(LOG_DEBUG);
	*/
	SetWindowState(FLAG_WINDOW_HIGHDPI);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
	SetTargetFPS(144);
	SetTraceLogLevel(LOG_DEBUG);
	SetExitKey(KEY_GRAVE);
}
