#pragma once
#include <vector>
#include <Actor/DrawableActor.h>
#include "Actor/Tail.h"

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);
	virtual void Update(float deltaTime) override;

	void KeyInputProcess();

	void PlayerMove(float deltaTime);

	const float Speed() { return speed; }
	const Direction getMoveDirection() { return moveDirection; }

private:
	Direction moveDirection;
	float speed = 1.5f;
	Vector2 lastMovePos;
	std::vector<Tail*> tail;

	GameLevel* ref = nullptr;
	bool isPlayer = true;
};