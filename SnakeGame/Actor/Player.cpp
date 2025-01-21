#include <Engine/Timer.h>
#include <Engine/Engine.h>
#include "Player.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("O"), lastMovePos(), moveDirection(Direction::DOWN), ref(level)
{
	this->position = position;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	KeyInputProcess();
	PlayerMove(deltaTime);
}

void Player::KeyInputProcess()
{
	// ESC ����.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
		// �޴� ���
		//Game::Get().ToggleMenu();
	}

	// �Է¿� ���� �̵����� ����
	if (Engine::Get().GetKeyDown(VK_UP)) moveDirection = Direction::UP;
	if (Engine::Get().GetKeyDown(VK_DOWN)) moveDirection = Direction::DOWN;
	if (Engine::Get().GetKeyDown(VK_LEFT)) moveDirection = Direction::LEFT;
	if (Engine::Get().GetKeyDown(VK_RIGHT)) moveDirection = Direction::RIGHT;
}

void Player::PlayerMove(float deltaTime)
{
	// ��� �ð� ����
	static float elapsedTime = 0.0f;
	// deltaTime�� ���� ����ð� ����
	elapsedTime += deltaTime * speed;

	// ��� �ð��� 1�� �ȵǸ� �� ����
	if (elapsedTime  < 1) return;

	// ��� �ð� �ʱ�ȭ
	elapsedTime = 0.0f;


	// �浹üũ
	if (ref->SnakeCollisionCheck())
	{
		// �÷��̾��� ���� ���� ó��
		if (isPlayer)
		{
			Engine::Get().QuitGame();
			return;
		}
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

