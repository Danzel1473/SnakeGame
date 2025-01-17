#include "Wall.h"

Wall::Wall(const Vector2& position, const char* image)
	:DrawableActor(image)
{
	this->position = position;
}
