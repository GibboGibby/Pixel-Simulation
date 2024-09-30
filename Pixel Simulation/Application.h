#pragma once
#include "Window.h"
#include <iostream>

class Application {
public:
	void Init();
	void Run();




private:
	Window window;
	bool gameStarted = true;
};