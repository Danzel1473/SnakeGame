#pragma once
#include <Actor/DrawableActor.h>
#include "Actor/Tail.h"
#include <vector>

class Player : public DrawableActor
{
public:
	Player(Vector2& position);

private:
	float speed = 1.0f;
	Vector2 lastMovePos;
	std::vector<Tail*> tail;
};