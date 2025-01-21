#pragma once
#include <Level/Level.h>
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include <vector>

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	bool CheckGameOver();

private:
	int score = 0;

	std::vector<DrawableActor*> map;
	std::vector<Tail*> tails;
	std::vector<Wall*> walls;
	Player* player = nullptr;
};