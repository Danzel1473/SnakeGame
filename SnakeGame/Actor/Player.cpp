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

	// �Է¿� ���� �̵����� ����
	if (Engine::Get().GetKeyDown(VK_UP)) moveDirection = Direction::UP;
	if (Engine::Get().GetKeyDown(VK_DOWN)) moveDirection = Direction::DOWN;
	if (Engine::Get().GetKeyDown(VK_LEFT)) moveDirection = Direction::LEFT;
	if (Engine::Get().GetKeyDown(VK_RIGHT)) moveDirection = Direction::RIGHT;

	// Todo: �ӵ��� ���� ���� �ð��� ���� �ʾҴٸ� �� ����
	if (speed * deltaTime < 1)
	{
		return;
	}

	Vector2 newPosition = position;

	// �̵����⿡ ���� Vector2�� �� ����
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

	// ���ο� ��ġ�� ����
	position = newPosition;
}

