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
	// ESC 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
		// 메뉴 토글
		//Game::Get().ToggleMenu();
	}

	// 입력에 따라 이동방향 설정
	if (Engine::Get().GetKeyDown(VK_UP)) moveDirection = Direction::UP;
	if (Engine::Get().GetKeyDown(VK_DOWN)) moveDirection = Direction::DOWN;
	if (Engine::Get().GetKeyDown(VK_LEFT)) moveDirection = Direction::LEFT;
	if (Engine::Get().GetKeyDown(VK_RIGHT)) moveDirection = Direction::RIGHT;
}

void Player::PlayerMove(float deltaTime)
{
	// 경과 시간 설정
	static float elapsedTime = 0.0f;
	// deltaTime에 따라 경과시간 증가
	elapsedTime += deltaTime * speed;

	// 경과 시간이 1이 안되면 얼리 리턴
	if (elapsedTime  < 1) return;

	// 경과 시간 초기화
	elapsedTime = 0.0f;


	// 충돌체크
	if (ref->SnakeCollisionCheck())
	{
		// 플레이어라면 게임 오버 처리
		if (isPlayer)
		{
			Engine::Get().QuitGame();
			return;
		}
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

