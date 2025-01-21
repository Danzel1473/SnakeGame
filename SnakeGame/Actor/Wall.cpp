#include "Wall.h"

Wall::Wall(const Vector2& position)
	:DrawableActor("W")
{
	this->position = position;

	color = Color::Purple;
}
