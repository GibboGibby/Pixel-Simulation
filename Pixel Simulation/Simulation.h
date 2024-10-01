#pragma once
#include "Pixel.h"
#include <array>

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
	void Render();

	void TogglePause() { paused = !paused; }

private:
	// WILL BE REPLACED WITH CHUNKS LATER
	std::array<std::array<Pixel, SCREEN_HEIGHT>, SCREEN_WIDTH> simulation;
	bool paused = false;
};