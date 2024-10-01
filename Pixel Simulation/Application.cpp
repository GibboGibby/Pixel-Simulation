#include "Application.h"
#include "Settings.h"

void Application::Init()
{
	window.Init(1920, 1080, "Pixel Simulation");
	//GuiLoadStyleCandy();
	GuiLoadStyleBluish();

	//DEBUG TESTING
#ifdef INSTANT_GAME
	gameState = GAME;
	previousState = GAME;
	std::cout << "Instant Game is enabled" << std::endl;
#endif
	
}

void Application::Run()
{
	while (appStarted)
	{
		if (WindowShouldClose()) 
		{ 
			appStarted = false;
			return; 
		}

		UpdateSwitch();


		BeginDrawing();
		ClearBackground({ 0,0,0,255 });

		RenderSwitch();
		if (g_Settings.drawFPS)
			DrawFPS(10, 20);
		EndDrawing();
	}

	CloseWindow();
}

void Application::UpdateMainMenu()
{
	if (IsKeyPressed(KEY_P))
	{
		std::cout << "Key P pressed" << std::endl;
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{
		appStarted = false;
		return;
	}
}

void Application::UpdatePauseMenu()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		//game->Pause(false);
		gameState = GAME;
	}
}

void Application::UpdateSettings()
{

}

void Application::RenderMainMenu()
{
	//if (GuiButton({ 835, 490, 250, 100 }, "Start Game"))
	if (GuiButton(GetRelativeRectBased({ 835, 490 },{250, 100}), "Start Game"))
	{
		gameState = GAME;
		previousState = GAME;
	}

	if (GuiButton(GetRelativeRectBased({ 835, 615 }, { 250, 100 }), "Settings"))
	{
		gameState = SETTINGS;
	}

	if (GuiButton(GetRelativeRectBased({ 835, 740 }, { 250, 100 }), "Quit To Main Menu"))
	{
		appStarted = false;
	}
}

void Application::RenderGame()
{
	game.Render();
}

void Application::RenderPauseMenu()
{
	if (GuiButton(GetRelativeRectBased({ 835, 490 }, { 250, 100 }), "Resume Game"))
	{
		gameState = GAME;
		previousState = GAME;
		//game->Pause(false);
	}

	if (GuiButton(GetRelativeRectBased({ 835, 615 }, { 250, 100 }), "Settings"))
	{

	}

	if (GuiButton(GetRelativeRectBased({ 835, 740 }, { 250, 100 }), "Quit To Main Menu"))
	{
		gameState = MAIN_MENU;
		game.Cleanup();
		//delete game;
		//game = nullptr;
	}
}

void Application::RenderSettings()
{
	if (GuiCheckBox(GetRelativeRectBased({ 835, 490 }, { 250, 100 }), "Draw FPS", &g_Settings.drawFPS))
	{
		std::cout << "Clicked" << std::endl;
	}
}

void Application::UpdateSwitch()
{
	switch (gameState)
	{
	case MAIN_MENU:
		previousState = MAIN_MENU;
		UpdateMainMenu();
		break;
	case GAME:
		//if (game == nullptr) game = new Game();
		game.Update();
		if (IsKeyPressed(KEY_ESCAPE)) { 
			//game->Pause(true);
			gameState = PAUSE_MENU;
		}
		break;
	case PAUSE_MENU:
		previousState = PAUSE_MENU;
		UpdatePauseMenu();
		break;
	case SETTINGS:
		UpdateSettings();
	default:
		break;
	}
}

void Application::RenderSwitch()
{
	switch (gameState)
	{
	case MAIN_MENU:
		RenderMainMenu();
		break;
	case GAME:
		game.Render();
		break;
	case PAUSE_MENU:
		RenderPauseMenu();
		break;
	case SETTINGS:
		RenderSettings();
	default:
		break;
	}
}
