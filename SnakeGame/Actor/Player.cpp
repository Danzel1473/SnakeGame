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

	// ���⼭ �浹 ó��.
	if (other->As<Pear>())
	{
		// ���� ����
		score += dynamic_cast<Pear*>(other)->GetScore();

		// �� ����.
		other->Destroy();
		
		// ���� ����
		SpawnTail();

		// ���ǵ� ����
		speed *= 1.1;

		return;
	}

	// �浹�� ��ü�� ���̳� ������ ���� ����.
	if (other->As<Wall>() || other->As<Tail>())
	{
		//���� �����
		Game::Get().LoadLevel(new GameLevel());
		Game::Get().Run();

		return;
	}
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
	if (tails.size() > 0)
	{
		if (Engine::Get().GetKeyDown(VK_UP) && lastDirection != Direction::DOWN)
			moveDirection = Direction::UP;
		if (Engine::Get().GetKeyDown(VK_DOWN) && lastDirection != Direction::UP)
			moveDirection = Direction::DOWN;
		if (Engine::Get().GetKeyDown(VK_LEFT) && lastDirection != Direction::RIGHT)
			moveDirection = Direction::LEFT;
		if (Engine::Get().GetKeyDown(VK_RIGHT) && lastDirection != Direction::LEFT)
			moveDirection = Direction::RIGHT;
	}
	else
	{
		if (Engine::Get().GetKeyDown(VK_UP)) moveDirection = Direction::UP;
		if (Engine::Get().GetKeyDown(VK_DOWN)) moveDirection = Direction::DOWN; 
		if (Engine::Get().GetKeyDown(VK_LEFT)) moveDirection = Direction::LEFT;
		if (Engine::Get().GetKeyDown(VK_RIGHT)) moveDirection = Direction::RIGHT;
	}
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

	Vector2 newPosition = position;

	// �̵����⿡ ���� Vector2�� �� ����, Tail�� �ִٸ� ���ϵ� �÷��̾ ���� �̵��ؾ���
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

	// ������ ������ �������� ����
	if (tails.size() > 0)
	{
		// ������ �̵� ����
		for (int i = 0; i < tails.size(); ++i)
		{
			tails[i]->SetLastMovePosition(tails[i]->GetPosition());
		
			if (i == 0)
			{
				tails[i]->SetPosition(lastMovePos);
				continue;
			}
		
			tails[i]->SetPosition(tails[i - 1]->GetLastMovePosition());

		}
	}

	// �浹üũ.
	ref->SnakeCollisionCheck(newPosition);

	// ���� ��ġ ����
	lastMovePos = position;
	lastDirection = moveDirection;
	// ���ο� ��ġ�� ����
	position = newPosition;
}

void Player::SpawnTail()
{
	Tail* tail;

	if (tails.size() > 0)
	{
		Vector2 pos = tails.back()->GetLastMovePosition();
		tail = new Tail(pos);
	}
	else
	{
		tail = new Tail(lastMovePos);
	}

	tails.push_back(tail);
	ref->AddActor(tail);
}

std::vector<Tail*> Player::GetTails()
{
	return tails;
}



