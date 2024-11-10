#include "windowsstuff.h"

#include "ClientGame.h"



ClientGame::ClientGame()
{
	Game::Game();
	gameType = CLIENT;
}

ClientGame::~ClientGame()
{
	Game::~Game();
}

void ClientGame::Init()
{
	Game::Init();
}

void ClientGame::Cleanup()
{
	Game::Cleanup();
}

void ClientGame::Update()
{

	//Game::Update();
}

void ClientGame::Render()
{
	Game::Render();
}