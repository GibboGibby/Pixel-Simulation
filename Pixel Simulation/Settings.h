#pragma once
#include "raylib.h"
#include <string>


struct GameSettings
{
	bool drawFPS = false;
	bool pauseGameInMenu = false;
};

extern GameSettings g_GameSettings;

static inline void SaveGameSettings()
{
	SaveFileData("GameSettings.gib", &g_GameSettings, sizeof(GameSettings));
}

static inline void LoadGameSettings()
{
	if (!FileExists("GameSettings.gib")) return;
	int size = 0;
	unsigned char* data = LoadFileData("GameSettings.gib", &size);

	memcpy(&g_GameSettings, data, size);
}