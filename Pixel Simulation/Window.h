#pragma once
#include <raylib.h>

class Window {

public:
	void Init(int width, int height, const char* stringName);
	void SetFPSTarget(int target) { SetTargetFPS(target); }
	void SetState(unsigned int flags) { SetWindowState(flags); }
	void SetFlags(unsigned int flags) { SetConfigFlags(flags); }
	void SetTraceLevel(int level) { SetTraceLogLevel(level); }
	void SetWindowExitKey(int key) { SetExitKey(key); }
};