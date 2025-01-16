#include "Tail.h"

Tail::Tail(Vector2* position)
	:DrawableActor("o")
{
	this->position = position;
}

void Tail::SetPosition(Vector2* position)
{
	this->position = position;
}

