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

	if (IsKeyPressed(KEY_ONE))	 selectedPixel.type = AIR; 
	if (IsKeyPressed(KEY_TWO))	 selectedPixel.type = WOOD;
	if (IsKeyPressed(KEY_THREE)) selectedPixel.type = SAND;
	if (IsKeyPressed(KEY_FOUR))  selectedPixel.type = WATER;


	if (IsKeyPressed(KEY_F6))
	{
		SaveSimulation();
	}
	if (IsKeyPressed(KEY_F7))
	{
		LoadSimulation();
	}

	Vector2 mosueWheel = GetMouseWheelMoveV();
	if (mosueWheel.y > 0)
	{
		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			selectedPixel.type = WheelscrollEnum(selectedPixel.type, 1);
		}

	}
	if (mosueWheel.y < 0)
	{
		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			selectedPixel.type = WheelscrollEnum(selectedPixel.type, -1);
		}
	}


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
		simulation[100][10] = { SAND };
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

	DrawText((("Selected Pixel is: " + selectedPixel.GetName()).c_str()), 10, 60, 20, GREEN);
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
			pixel->hasCollided = false;
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
#ifdef LOOP_FROM_BOTTOM
		for (int y= ySize - 1; y > 0; y--)
		//for (int y = 0; y < ySize; y++)
		{
			PixelStep(x, y);
		}
#else
		for (int y = 0; y < ySize; y++)
		{
			PixelStep(x, y);
		}
#endif
	}
}

void Simulation::PixelStep(int x, int y)
{
	Pixel* pixel = &simulation[x][y];
	PixelData data = PixelDataTable.at(pixel->type);
	bool onGround = false;
	bool hasMoved = false;
	if (pixel->hasUpdated) return;
	if ((y + 1) >= SCREEN_HEIGHT) return;

	if (CheckFlag(pixel, MOVE_Y))
	{
		pixel->vel.y -= data.accel * GetFrameTime();
		pixel->hasUpdated = true;

		pixel->vel.y = Min(pixel->vel.y, data.max_speed);



		if (CheckFlag(pixel, FALL))
		{
			float absVal = fabs(pixel->vel.y);
			int actualVel = ceil(absVal);
			//std::cout << "y vel - " << pixel->vel.y << " | abs y - " << absVal << " | and actual vel - " << actualVel << std::endl;
			//std::cout << "Pixel is falling with vel of " << absVal << std::endl;
			Pixel* nextPixel = GetNextDownPixel(x, y, actualVel);
			if (nextPixel == pixel) hasMoved = true;
			SwapPixels(pixel, nextPixel);
			pixel = nextPixel;
		}
	}

	onGround = IsPixelIsOnGround(x, y);

	if (CheckFlag(pixel, MOVE_X) && pixel->hasCollided && onGround)
	{
		bool rightFirst = RandomBool();
		int dir = (rightFirst) ? 1 : -1;

		//Check First Dir
		int firstX = x + dir;
		int secondX = x + dir * -1;
		if (firstX < SCREEN_WIDTH && firstX > 0)
		{
			if (simulation[firstX][y].type == AIR)
			{
				Pixel* other = &simulation[firstX][y];
				SwapPixels(pixel, other);
				pixel = other;
				hasMoved = true;
			}
		}
		if (secondX < SCREEN_WIDTH && secondX > 0)
		{
			if (simulation[secondX][y].type == AIR)
			{
				Pixel* other = &simulation[secondX][y];
				SwapPixels(pixel, other);
				pixel = other;
				hasMoved = true;
			}
		}
	}
	// TODO: Need to add x-to-y splat so that it is less uniform
	if (CheckFlag(pixel, MOVE_DIAG) && pixel->hasCollided && onGround)
	{
		int rightX = x +1;
		int leftX = x-1;
		int newY = y+1;
		if (newY >= SCREEN_WIDTH) return;
		if (!simulation[x][y+1].type == AIR)
		{
			if (CheckLeftDiagonal(x, y))
			{
				Pixel* other = &simulation[leftX][newY];
				SwapPixels(pixel, other);
				pixel = other;
				hasMoved = true;
			}
			
			if (CheckRightDiagonal(x, y))
			{
				Pixel* other = &simulation[rightX][newY];
				SwapPixels(pixel, other);
				pixel = other;
				hasMoved = true;
			}
		}
	}

	if (pixel->hasCollided) pixel->vel.y = 0.0f;
	
	if (hasMoved) {
		pixel->isResting = false;
	}
	else
	{
		pixel->isResting = true;
	}
	
	/*
	if (pixel->type == SAND)
	{
		if (simulation[x][y + 1].type == AIR)
		{
			pixel->hasUpdated = true;
			SwapPixels(&simulation[x][y + 1], pixel);
		}
	}
	*/
	


}

void Simulation::SwapPixels(Pixel* a, Pixel* b)
{
	Pixel temp = *a;
	*a = *b;
	*b = temp;
	a->hasUpdated = true;
	b->hasUpdated = true;
}

Pixel* Simulation::GetNextDownPixel(int x, int y, int dist)
{
	Pixel* lastGoodPixel = &simulation[x][y];
	//std::cout << "dist value - " << dist << std::endl;
	for (int i = 1; i <= dist; i++)
	{
		int newY = y + i;
		if (newY > SCREEN_HEIGHT-1) break;
		Pixel* temp = &simulation[x][newY];
		//std::cout << i << "th value" << std::endl;
		if (temp->type == AIR)
		{
			lastGoodPixel = &simulation[x][newY];
			//simulation[x][y].vel.y += 1;
			//std::cout << "Last good air is at x: " << x << " y: " << y << std::endl;
		}
		else
		{
			//if (lastGoodPixel->type != simulation[x][y].type)
				simulation[x][y].hasCollided = true;
			break;
		}
	}
	return lastGoodPixel;
}

bool Simulation::IsPixelIsOnGround(int x, int y)
{
	if (y + 1 > SCREEN_HEIGHT - 1) return false;
	Pixel* curPixel = &simulation[x][y];
	Pixel* pixel = &simulation[x][y+1];
	if (curPixel->hasCollided) return true;
	if (curPixel->isResting) return true;
	return false;
}

bool Simulation::CheckLeftDiagonal(int x, int y)
{
	int newX = x - 1;
	int newY = y + 1;

	if (newX < 0) return false;
	if (newY > SCREEN_HEIGHT - 1) return false;
	if (simulation[newX][y].type != AIR) return false;
	if (simulation[newX][newY].type == AIR) return true;
	return false;
}

bool Simulation::CheckRightDiagonal(int x, int y)
{
	int newX = x + 1;
	int newY = y + 1;

	if (newX > SCREEN_WIDTH-1) return false;
	if (newY > SCREEN_HEIGHT - 1) return false;
	if (simulation[newX][y].type != AIR) return false;
	if (simulation[newX][newY].type == AIR) return true;
	return false;
}

void Simulation::SaveSimulation()
{
	std::vector<std::vector<PixelSerialized>> serialized(SCREEN_WIDTH, std::vector<PixelSerialized>(SCREEN_HEIGHT));
	
	//std::unique_ptr<std::array<std::array<PixelSerialized, SCREEN_HEIGHT>, SCREEN_WIDTH>> serialized = std::make_unique<std::array<std::array<PixelSerialized, SCREEN_HEIGHT>, SCREEN_WIDTH>>();
	for (int x = 0; x < simulation.size(); x++)
	{
		for (int y = 0; y < simulation[0].size(); y++)
		{
			serialized[x][y] = { simulation[x][y].type, simulation[x][y].variant };
			//serialized[x][y].type = simulation[x][y].type;
			//serialized[x][y].variant = simulation[x][y].variant;
		}
	}

	std::vector<PixelSerialized> flatArray(SCREEN_HEIGHT * SCREEN_WIDTH);
	for (const auto& row : serialized)
	{
		flatArray.insert(flatArray.end(), row.begin(), row.end());
	}

	SaveFileData("save_data.gib", simulation.data(), sizeof(simulation));
}

void Simulation::LoadSimulation()
{
	//std::unique_ptr<std::array<std::array<PixelSerialized, SCREEN_HEIGHT>, SCREEN_WIDTH>> serialized = std::make_unique<std::array<std::array<PixelSerialized, SCREEN_HEIGHT>, SCREEN_WIDTH>>();
	
	//std::vector<std::vector<PixelSerialized>> serialized(SCREEN_WIDTH, std::vector<PixelSerialized>(SCREEN_HEIGHT));
	int size = sizeof(simulation);
	unsigned char* bytes = LoadFileData("save_data.gib", &size);
	memcpy(&simulation, bytes, size);
	
	/*
	for (int x = 0; x < simulation.size(); x++)
	{
		for (int y = 0; y < simulation[0].size(); y++)
		{
			//simulation[x][y].type = serialized[x][y].type;
			//simulation[x][y].variant = serialized[x][y].variant;
			simulation[x][y] = { serialized[x][y].type, serialized[x][y].variant };
		}
	}
	*/
	
}