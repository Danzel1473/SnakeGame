#pragma once
#include <Actor/DrawableActor.h>

class Wall : public DrawableActor
{
	RTTI_DECLARATIONS(Wall, DrawableActor)

public:
	Wall(const Vector2& position, const char* image);

private:
	
};