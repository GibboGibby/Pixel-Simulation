#pragma once
#include "raylib.h"
#include <random>
#include <functional>

//
inline Rectangle GetRelativeRectPercent(Vector2 origin, Vector2 size)
{
	int width = GetScreenWidth();
	int height = GetScreenHeight();
	Rectangle rect;
	rect.x = (origin.x / 100.0f) * (float)width;
	rect.y = (origin.y / 100.0f) * (float)height;

	rect.width = (size.x / 100.0f) * (float)width;
	rect.height = (size.y / 100.0f) * (float)height;
	return rect;
}

inline Rectangle GetRelativeRectBased(Vector2 origin, Vector2 size, Vector2 baseResolution = { 1920,1080 })
{
	int width = GetScreenWidth();
	int height = GetScreenHeight();

	float xScale = (float)width / baseResolution.x;
	float yScale = (float)height / baseResolution.y;

	Rectangle rect;
	rect.x = origin.x * xScale;
	rect.y = origin.y * yScale;

	rect.width = size.x * xScale;
	rect.height = size.y * yScale;
	return rect;
}

inline float GetCenteredX(int size)
{
	return (float)(GetScreenWidth() / 2) - (size / 2);
}

inline float GetCenteredY(int size)
{
	return (float)(GetScreenHeight() / 2) - (size / 2);
}

inline bool randomBool() {
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
	return gen();
}