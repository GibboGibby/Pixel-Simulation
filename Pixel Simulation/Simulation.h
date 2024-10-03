#pragma once
#include "Pixel.h"
#include "PlacingCrosshair.h"
#include <array>
#include "Maths.h"

const int SCREEN_WIDTH = 192 * 3;
const int SCREEN_HEIGHT = 108 * 3;

class Simulation
{
public:
	Simulation();
	~Simulation() {}

	Simulation(const Simulation&) = delete;
	Simulation& operator=(const Simulation&) = delete;

	void Update();
	void SetPixel(int x, int y, PixelType type);
	void SetPixelRange(int x, int y, int width, int height, PixelType type);
	void Render();
	void RenderSimulation();

	Vec2 ScreenToSimulationPosition(Vec2 pos);

	Vec2 SimulationToScreenPosition(Vec2 pos);

	void SimulationStep();
	void PixelStep(int x, int y);

	void TogglePause() { paused = !paused; }

	void SwapPixels(Pixel* a, Pixel* b);

	Pixel* GetNextDownPixel(int x, int y, int dist);	`

private:

	// WILL BE REPLACED WITH CHUNKS LATER
	std::array<std::array<Pixel, SCREEN_HEIGHT>, SCREEN_WIDTH> simulation;
	std::array<std::array<Color, SCREEN_WIDTH>, SCREEN_HEIGHT> colourBuffer;
	Texture2D screenTexture;
	bool paused = false;
	float relativeScale = 1.0f;
	Pixel selectedPixel = { WOOD }; 
	PlacingCrosshair placingCrosshair;
};