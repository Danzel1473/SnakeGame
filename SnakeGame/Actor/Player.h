#pragma once
#include <vector>
#include <Actor/DrawableActor.h>
#include "Actor/Tail.h"

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);
	virtual void Update(float deltaTime) override;

	virtual void OnCollision(Actor* other) override;

	void KeyInputProcess();

	void PlayerMove(float deltaTime);
	void SpawnTail();
	std::vector<Tail*> GetTails();

	const int Score() { return score; }
	const float Speed() { return speed; }
	const Direction GetMoveDirection() { return moveDirection; }

	std::vector<Tail*> tails;
private:
	Direction moveDirection;
	Direction lastDirection = Direction::NONE;
	float speed = 2.0f;
	Vector2 lastMovePos;


	int score = 0;

	GameLevel* ref = nullptr;
	bool isPlayer = true;
};