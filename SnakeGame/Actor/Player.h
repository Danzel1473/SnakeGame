#pragma once
#include <Actor/DrawableActor.h>
#include "Actor/Tail.h"
#include <vector>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position);
	virtual void Update(float deltaTime) override;

	const float Speed() { return speed; }
	const Direction getMoveDirection() { return moveDirection; }

private:
	Direction moveDirection;
	float speed = 1.2f;
	Vector2 lastMovePos;
	std::vector<Tail*> tail;
};