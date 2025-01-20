#include "GameLevel.h"
#include "string"

GameLevel::GameLevel()
{
    const char* mapString = "1111111111111\n1           1\n1           1\n1           1\n1           1\n1111111111111";

    for (int i = 0; i < strlen(mapString); i++)
    {
        static int x = 0;
        static int y = 0;

        if (mapString[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }

        if (mapString[i] == '1')
        {
            Wall* wall = new Wall(Vector2(y, x));
            walls.push_back(wall);
            x++;
            
            continue;
        }

        x++;
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
