#include "Simulation.h"
#include <iostream>
Simulation::Simulation()
{
	//memset(&simulation[0][0], AIR, sizeof(simulation));

	for (int i = 0; i < colourBuffer.size(); i++)
	{
		for (int j = 0; j < colourBuffer[0].size(); j++)
		{
			colourBuffer[i][j] = BROWN;
			simulation[j][i] = { AIR };
		}
	}

	Image screenImage = { 0 };
	screenImage.data = colourBuffer.data();
	screenImage.width = SCREEN_WIDTH;
	screenImage.height = SCREEN_HEIGHT;
	screenImage.mipmaps = 1;
	screenImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	//UpdateTexture(screenTexture, colourBuffer->data());
	screenTexture = LoadTextureFromImage(screenImage);
}

void Simulation::Update()
{
	relativeScale = static_cast<float>(GetScreenHeight()) / static_cast<float>(SCREEN_HEIGHT);

	Vector2 mousePos = GetMousePosition();

	if (IsKeyPressed(KEY_ONE)) { selectedPixel.type = AIR; } 
	if (IsKeyPressed(KEY_TWO)) { selectedPixel.type = WOOD; std::cout << "Wood Selected" << std::endl; }
	if (IsKeyPressed(KEY_THREE)) selectedPixel.type = SAND;


	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 temp = { mousePos.x / relativeScale, mousePos.y / relativeScale };
		Vector2 size = placingCrosshair.GetSize();
		SetPixelRange(temp.x, temp.y, size.x, size.y, { selectedPixel.type});
		//simulation[temp.x][temp.y] = { SAND };
	}

	placingCrosshair.Update();


	if (IsKeyDown(KEY_P))
	{
		for (int i = 0; i < 75; i++)
		{
			for (int j = 0; j < 75; j++)
			{
				simulation[10 + i][10 + j] = SAND;
			}
		}
	}

	SimulationStep();
}

Vec2 Simulation::ScreenToSimulationPosition(Vec2 pos)
{
	return Vec2(pos.x / relativeScale, pos.y / relativeScale);
}

Vec2 Simulation::SimulationToScreenPosition(Vec2 pos)
{
	return Vec2(pos.x * relativeScale, pos.y * relativeScale);
}

void Simulation::SetPixel(int x, int y, PixelType type)
{
	simulation[x][y] = { type };
}

void Simulation::SetPixelRange(int x, int y, int width, int height, PixelType type)
{
	Vector2 mousePos = GetMousePosition();
	if (mousePos.x < 0 || mousePos.x > GetScreenWidth() || mousePos.y < 0 || mousePos.y > GetScreenHeight()) return;
	Vec2 pos = { (int)mousePos.x - width / 2, (int)mousePos.y - height / 2 };


	Vec2 temp = ScreenToSimulationPosition(pos);
	//if (temp.x >= SCREEN_WIDTH || temp.x < 0 || temp.y >= SCREEN_HEIGHT || temp.y < 0) return;
	int sizeX = width / relativeScale;
	int sizeY = height / relativeScale;


	int screen_width = SCREEN_WIDTH;
	int screen_height = SCREEN_HEIGHT;
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			int newX = temp.x + x; 
			int newY = temp.y + y;
			if (newX < 0 || newX >= screen_width || newY < 0 || newY >= screen_height) continue;
			simulation[newX][newY] = { type };
		}
	}
}

void Simulation::Render()
{
	RenderSimulation();

	placingCrosshair.Render();
}

void Simulation::RenderSimulation()
{
	int xSize = simulation.size();
	int ySize = simulation[0].size();
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			Pixel* pixel = &simulation[x][y];
			colourBuffer[y][x] = pixel->GetColor();
			pixel->hasUpdated = false;
		}
	}

	Rectangle sourceRec = { 0, 0, static_cast<float>(screenTexture.width), static_cast<float>(screenTexture.height) };
	Rectangle destRec = { 0,0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
	Vector2 origin = { 0,0 };
	float rotation = 0.0f;
	UpdateTexture(screenTexture, colourBuffer.data());
	DrawTexturePro(screenTexture, sourceRec, destRec, origin, rotation, WHITE);
}

void Simulation::SimulationStep()
{
	if (paused) return;
	int xSize = simulation.size();
	int ySize = simulation[0].size();
	for (int x = 0; x < xSize; x++)
	{
		//for (int y= ySize - 1; y > 0; y--)
		for (int y = 0; y < ySize; y++)
		{
			PixelStep(x, y);
		}
	}
}

void Simulation::PixelStep(int x, int y)
{
	Pixel* pixel = &simulation[x][y];
	if (pixel->hasUpdated) return;
	if (y > 300) return;
	if (pixel->type == SAND)
	{
		if (simulation[x][y + 1].type == AIR)
		{
			pixel->hasUpdated = true;
			SwapPixels(&simulation[x][y + 1], pixel);
		}
	}


}

void Simulation::SwapPixels(Pixel* a, Pixel* b)
{
	Pixel temp = *a;
	*a = *b;
	*b = temp;
}
