#include "Tail.h"

Tail::Tail(const Vector2& position)
	:DrawableActor("o")
{
	this->position = position;
	lastMovePosition = position;

	color = Color::Mint;
}

void Tail::SetPosition(const Vector2& position)
{
	this->position = position;
}

Vector2 Tail::GetPosition()
{
	return position;
}

Vector2 Tail::GetLastMovePosition()
{
	return lastMovePosition;
}

void Tail::SetLastMovePosition(const Vector2& position)
{
	lastMovePosition = position;
}
