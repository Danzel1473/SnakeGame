#include "Player.h"
#include<Engine/Engine.h>
#include <Engine/Timer.h>

Player::Player(const Vector2& position)
	:DrawableActor("O"), lastMovePos(), tail(0), moveDirection(Direction::DOWN)
{
	this->position = position;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 입력에 따라 이동방향 설정
	if (Engine::Get().GetKeyDown(VK_UP)) moveDirection = Direction::UP;
	if (Engine::Get().GetKeyDown(VK_DOWN)) moveDirection = Direction::DOWN;
	if (Engine::Get().GetKeyDown(VK_LEFT)) moveDirection = Direction::LEFT;
	if (Engine::Get().GetKeyDown(VK_RIGHT)) moveDirection = Direction::RIGHT;

	// Todo: 속도에 따른 일정 시간이 되지 않았다면 얼리 리턴
	if (speed * deltaTime < 1)
	{
		return;
	}

	Vector2 newPosition = position;

	// 이동방향에 따라 Vector2의 값 설정
	switch (moveDirection)
	{
	case Direction::UP:
		newPosition.y = --position.y;
		break;
	case Direction::DOWN:
		newPosition.y = ++position.y;
		break;
	case Direction::LEFT:
		newPosition.x = --position.x;
		break;
	case Direction::RIGHT:
		newPosition.x = ++position.x;
		break;
	default:
		break;
	}

	// 새로운 위치로 적용
	position = newPosition;
}

