#include "GameLevel.h"
#include <Engine/Engine.h>
#include <string>

GameLevel::GameLevel()
{
    std::string mapString = 
        "1111111111111111111111111\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1                       1\n"
        "1111111111111111111111111";
    int x = 0;
    int y = 0;

    // 맵 해석
    for (int i = 0; i < mapString.size(); i++)
    {
        if (mapString[i] == '\n')
        {
            ++y;
            x = 0;
            continue;
        }

        if (mapString[i] == '1')
        {
            Wall* wall = new Wall(Vector2(x, y));
            walls.push_back(wall);
            actors.push_back(wall);
        }

        ++x;
    }

    // 플레이어 추가
    player = new Player(Vector2(((int)mapString.size() / 17) / 2, 8), this);
    actors.push_back(player);
}

void GameLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // 주기적으로 배(과일) 생성
    SpawnPear(deltaTime);

}

void GameLevel::Draw()
{
    player->tails.clear();
    for (auto* actor : actors)
    {
        auto* tail = actor->As<Tail>();
        if (tail)
        {
            player->tails.emplace_back(tail);
        }
    }
    // 벽 그리기
    for (auto* wall : walls)
    {
        wall->Draw();
    }

    // 배 그리기.
    pears.clear();
    for (auto* actor : actors)
    {
        auto* pear = actor->As<Pear>();
        if (pear)
        {
            pears.emplace_back(pear);
        }
    }

    if (pears.size() > 0)
    {
        for (auto* pear : pears)
        {
            pear->Draw();
        }
    }
    pears.clear();



    if (player->GetTails().size() > 0)
    {
        for (auto* tail : player->GetTails())
        {
            tail->Draw();
        }
    }

    player->Draw();

    char buffer[24];
    sprintf_s(buffer, "Score: %d", player->Score());
    const char* scoreString = buffer;

    Engine::Get().Draw(Vector2(0, 17), scoreString);
}

void GameLevel::SpawnPear(float deltaTime)
{
    static float elapsedTime = 0.0f;
    static float spawnTime = 5.0f;

    // 타이머
    elapsedTime += deltaTime;
    if (elapsedTime < spawnTime) return;

    // 타이머 리셋
    elapsedTime = 0.0f;

    int pearX = 0;
    int pearY = 0;

    while (true)
    {
        pearX = (int)RandomPercent(1.0f, 24.0f);
        pearY = (int)RandomPercent(1.0f, 16.0f);

        if (DuplicationCheck(pearX, pearY))
        {
            continue;
        }

        break;
    }

    // 배 생성
    Pear* pear = new Pear(Vector2(pearX, pearY));
    actors.push_back(pear);
}

bool GameLevel::DuplicationCheck(int x, int y)
{
    for (auto actor : actors)
    {
        if (actor->Position().x == x && actor->Position().y == y)
        {
            return true;
        }
    }
    return false;
}

bool GameLevel::SnakeCollisionCheck(Vector2 position)
{
    // 플레이어를 기준으로 충돌 처리.
    for (auto actor : actors)
    {
        if (actor->As<Player>()) continue;

        if (actor->Position() == position)
        {
            player->OnCollision(actor);
            return false;
        }
    }

    return false;
}

bool GameLevel::CheckGameOver()
{
    return false;
}
