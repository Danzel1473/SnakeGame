#pragma once
#include <Level/Level.h>
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Pear.h"
#include <vector>

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void SpawnPear(float deltaTime);

	bool DuplicationCheck(int pearX, int pearY);

	bool SnakeCollisionCheck(Actor* a, Actor* b = nullptr);
	bool SnakeCollisionCheck(Vector2 Position);

private:
	bool CheckGameOver();

private:

	std::vector<DrawableActor*> map;
	std::vector<Wall*> walls;
	std::vector<Pear*> pears;

	Player* player = nullptr;
};