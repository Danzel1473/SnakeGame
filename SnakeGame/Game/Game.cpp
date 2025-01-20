#include "Game.h"
#include "Level/GameLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	:Engine()
{
	instance = this;
}

Game::~Game()
{

}

void Game::ToggleMenu()
{

}