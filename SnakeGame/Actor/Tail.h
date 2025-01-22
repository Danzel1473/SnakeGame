#pragma once
#include <Actor/DrawableActor.h>

class Tail : public DrawableActor
{
	RTTI_DECLARATIONS(Tail, DrawableActor)

public:
	Tail(const Vector2& position);

	Vector2 GetPosition();
	Vector2 GetLastMovePosition();

	void SetPosition(const Vector2& position);
	void SetLastMovePosition(const Vector2& position);

private:
	Vector2 position;
	Vector2 lastMovePosition;
};