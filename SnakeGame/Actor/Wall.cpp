#include "Wall.h"

Wall::Wall(const Vector2& position)
	:DrawableActor("бр")
{
	this->position = position;

	color = Color::Green;
}
