#pragma once
#include "Window.h"
#include <iostream>

#include "raygui.h"
#include "style_candy.h"
#include "style_bluish.h"
#include "Game.h"
#include "Helpers.h"


enum GameState {
	MAIN_MENU,
	GAME,
	PAUSE_MENU,
	SETTINGS
};

class Application {
public:
	void Init();
	void Run();

	void UpdateMainMenu();
	void UpdatePauseMenu();
	void UpdateSettings();

	void RenderMainMenu();
	void RenderGame();
	void RenderPauseMenu();
	void RenderSettings();

	void UpdateSwitch();
	void RenderSwitch();

private:
	Window window;
	bool appStarted = true;
	GameState gameState = MAIN_MENU;
	Game game;
	GameState previousState = MAIN_MENU;

	Font mainMenuButtonFont;
};