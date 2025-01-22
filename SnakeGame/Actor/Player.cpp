#include <Engine/Timer.h>
#include <Engine/Engine.h>
#include "Player.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

#include "Actor/Pear.h"
#include "Actor/Wall.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("O"), lastMovePos(), moveDirection(Direction::DOWN), ref(level)
{
	this->position = position;
	lastMovePos = position;
	color = Color::Mint;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	KeyInputProcess();
	PlayerMove(deltaTime);
}

void Player::OnCollision(Actor* other)
{
	Super::OnCollision(other);

	// 여기서 충돌 처리.
	if (other->As<Pear>())
	{
		// 점수 증가
		score += dynamic_cast<Pear*>(other)->GetScore();

		// 배 제거.
		other->Destroy();

		// 꼬리 생성
		SpawnTail();

		// 스피드 증가
		speed *= 1.1;
		
		return;
	}

	// 충돌한 물체가 벽이면 게임 종료.
	if (other->As<Wall>())
	{
		Engine::Get().QuitGame();
		return;
	}
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

	Vector2 newPosition = position;

	// 이동방향에 따라 Vector2의 값 설정, Tail이 있다면 테일도 플레이어를 따라 이동해야함
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
	}

	// 충돌체크.
	ref->SnakeCollisionCheck(newPosition);

	// 이전 위치 저장
	lastMovePos = position;
	// 새로운 위치로 적용
	position = newPosition;

	if (tails.size() > 0)
	{
		// 꼬리의 이동 루프
		for (int i = 0; i < tails.size(); ++i)
		{
			tails[i]->SetLastMovePosition(tails[i]->GetPosition());
		
			if (i == 0)
			{
				tails[i]->SetPosition(lastMovePos);
				break;
			}
		
			tails[i]->SetPosition(tails[i - 1]->GetLastMovePosition());

		}
	}
}

void Player::SpawnTail()
{
	Tail* tail;

	if (tails.size() < 1)
	{
		tail = new Tail(lastMovePos);
	}
	else
	{
		Vector2 pos = tails.back()->GetLastMovePosition();
		tail = new Tail(pos);
	}

	tails.push_back(tail);
	ref->AddActor(tail);
}

std::vector<Tail*> Player::GetTails()
{
	return tails;
}



