#pragma once
#include <Actor/DrawableActor.h>

class Tail : public DrawableActor
{
	RTTI_DECLARATIONS(Tail, DrawableActor)

public:
	Tail(Vector2* position);
	void SetPosition(Vector2* position);

private:
	Vector2* position;
};