#pragma once
#include <Actor/DrawableActor.h>


class Pear : public DrawableActor
{
	RTTI_DECLARATIONS(Pear, DrawableActor)

public:
	Pear(Vector2 position);

	int GetScore() { return score; }

private:
	int score = 10;
};