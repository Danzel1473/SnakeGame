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
    player = new Player(Vector2((mapString.size() / 17) / 2, 8), this);
    actors.push_back(player);
}

void GameLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Todo: 주기적으로 맵의 x, y값에 따른 random값을 2개 구하고
    // actor를 전부 순회하여 랜덤으로 구한 위치에 액터가 존재하면 다시 랜덤 x,y값을 구한다.
    // 액터가 없는 위치라면 pear 객체를 그 위치에 생성한다.

}

void GameLevel::Draw()
{
    // 벽 그리기
    for (auto* wall : walls)
    {
        wall->Draw();
    }

    player->Draw();
}

bool GameLevel::SnakeCollisionCheck()
{
    for (auto actor : actors)
    {
        if (actor->As<Player>()) continue;

        Vector2 nextPos = player->Position();
        switch (player->getMoveDirection())
        {
        case Direction::UP:
            ++nextPos.y;
            break;
        case Direction::DOWN:
            --nextPos.y;
        case Direction::LEFT:
            --nextPos.x;
            break;
        case Direction::RIGHT:
            ++nextPos.x;
            break;
        }
        
        if (actor->Position() == nextPos)
        {
            return true;
        }
    }

    return false;
}

bool GameLevel::CheckGameOver()
{
    return false;
}
