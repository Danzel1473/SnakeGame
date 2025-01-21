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
    //for (int i = 0; i < strlen(mapString); i++)
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

    player = new Player(Vector2((mapString.size() / 17) / 2, 8));

    actors.push_back(player);

    //Todo: 맵의 x, y 크기를 계산해서 저장,
}

void GameLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Todo: 주기적으로 맵의 x, y값에 따른 random값을 2개 구하고
    // actor를 전부 순회하여 랜덤으로 구한 위치에 액터가 존재하면 다시 랜덤 x,y값을 구한다.
    // 액터가 없는 위치라면 pear 객체를 그 위치에 생성한다.

    // Todo:플레이어의 충돌체크. 벽이나 Tail에 충돌시 게임오버
}

void GameLevel::Draw()
{
    // 벽 그리기
    for (auto* wall : walls)
    {
        wall->Draw();
    }

    player->Draw();

    Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 1);
    Log("Score: %d", score);
    // Todo: 액터 그리기
}

bool GameLevel::CheckGameOver()
{
    return false;
}
