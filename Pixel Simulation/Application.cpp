#include "Application.h"

void Application::Init()
{
	window.Init(1920, 1080, "Pixel Simulation");
}

void Application::Run()
{
	while (gameStarted)
	{
		if (WindowShouldClose()) 
		{ 
			gameStarted = false;
			return; 
		}

		if (IsKeyDown(KEY_P))
		{
			std::cout << "P has been pressed" << std::endl;
		}

		BeginDrawing();
		ClearBackground({ 0,0,0,255 });
		EndDrawing();
	}

	CloseWindow();
}
