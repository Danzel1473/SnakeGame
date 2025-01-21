#include "GameLevel.h"
#include <string>

GameLevel::GameLevel()
{
    std::string mapString = "11\n1 1 1";
    int x = 0;
    int y = 0;

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
        }

        ++x;
    }
}

void GameLevel::Update(float deltaTime)
{

}

void GameLevel::Draw()
{
    for (auto* wall : walls)
    {
        wall->Draw();
    }

    // 액터 그리기

}

bool GameLevel::CheckGameOver()
{
    return false;
}
