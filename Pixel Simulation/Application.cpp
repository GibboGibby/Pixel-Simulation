#include "Application.h"
#include "Settings.h"

#define INSTANT_GAME

void Application::Init()
{
	window.Init(1920, 1080, "Pixel Simulation");
	//GuiLoadStyleCandy();
	GuiLoadStyleBluish();
	LoadGameSettings();
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
	mainMenuButtonFont = LoadFontEx("resources/font/homespun.ttf", 100, NULL, 0);
	//GuiSetFont(mainMenuButtonFont);

	//DEBUG TESTING
#ifdef INSTANT_GAME
	gameState = GAME;
	previousState = GAME;
	game.Init();
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
		ClearBackground({ 180,203,240,255 });

		RenderSwitch	();
		if (g_GameSettings.drawFPS)
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
		if (g_GameSettings.pauseGameInMenu) game.Pause(false);
		gameState = GAME;
	}
}

void Application::UpdateSettings()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		SaveGameSettings();
		gameState = previousState;
	}
}

void Application::RenderMainMenu()
{
	GuiSetStyle(BUTTON, TEXT_PADDING, 10);
	GuiSetStyle(DEFAULT, TEXT_SPACING, 2);
	//GuiTextBox({ 300,100, 1320, 200 }, guiText, 300, true);
	
	//DrawText("Pixel Simulation", 750, 250, 60, WHITE);
	DrawText("Pixel Simulation", GetScreenWidth() / 2 - MeasureText("Pixel Simulation", 60) / 2, 250, 60, WHITE);
	DrawText("By James Gibson", GetScreenWidth() / 2 - MeasureText("By James Gibson", 24) / 2, 350, 24, BLUE);

	//GuiSetFont(mainMenuButtonFont);
	//if (GuiButton({ 835, 490, 250, 100 }, "Start Game"))
	//if (GuiButton(GetRelativeRectBased({ 835, 490 },{250, 100}), "Start Game"))
	if (GuiButton({GetCenteredX(250),490, 250, 100 }, "Start Game"))
	{
		gameState = GAME;
		previousState = GAME;
		game.Init();
	}

	if (GuiButton(GetRelativeRectBased({ 835, 615 }, { 250, 100 }), "Settings"))
	{
		gameState = SETTINGS;
	}

	if (GuiButton(GetRelativeRectBased({ 835, 740 }, { 250, 100 }), "Quit To Desktop"))
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
		gameState = SETTINGS;
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
	if (GuiButton(GetRelativeRectBased({ 50,50 },{50, 50}), "Back"))
	{
		gameState = previousState;
		SaveGameSettings();
	}

	if (GuiCheckBox(GetRelativeRectBased({ 835, 490 }, { 50, 50 }), "Draw FPS", &g_GameSettings.drawFPS))
	{
		std::cout << "Clicked" << std::endl;
	}

	if (GuiCheckBox(GetRelativeRectBased({ 835, 550 }, { 50, 50 }), "Pause Simulation In Menus", &g_GameSettings.pauseGameInMenu))
	{
		std::cout << "Clicked" << std::endl;
	}

	if (GuiCheckBox(GetRelativeRectBased({ 835, 610 }, { 50, 50 }), "Loop From Bottom", &g_GameSettings.loopFromBottom))
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

			if (g_GameSettings.pauseGameInMenu) game.Pause(true);
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
