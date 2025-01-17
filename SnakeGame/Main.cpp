#include "Game/Game.h"
#include "Level/GameLevel.h"

int main()
{
	Game game;
	game.Get().LoadLevel(new GameLevel());
	game.Get().Run();
}