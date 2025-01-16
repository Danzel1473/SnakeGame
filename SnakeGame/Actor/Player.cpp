#include "Player.h"

Player::Player(Vector2& position)
	:DrawableActor("O"), lastMovePos(), tail(0)
{
	this->position = position;

}
