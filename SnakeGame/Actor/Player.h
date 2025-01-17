#pragma once
#include <Actor/DrawableActor.h>
#include "Actor/Tail.h"
#include <vector>

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(Vector2& position);
	const float Speed() { return speed; }

private:
	float speed = 1.0f;
	Vector2 lastMovePos;
	std::vector<Tail*> tail;
};