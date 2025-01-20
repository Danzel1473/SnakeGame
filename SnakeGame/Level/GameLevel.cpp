#include "GameLevel.h"
#include "string"

GameLevel::GameLevel()
{
    const char* mapString = "��";

    for (int i = 0; i < strlen(mapString); i++)
    {
        static int x = 0;
        static int y = 0;
        if (mapString[i] == ' ')
        {
            x++;
            continue;
        }

        if (mapString[i] == '\n')
        {
            y++;
            continue;
        }
        char a = mapString[i];
        const char* mapChar = new char(a);

        Wall* wall = new Wall(Vector2(x, y), mapChar);
        walls.push_back(wall);
        x++;

        delete mapChar;
    }

}

void GameLevel::Update(float deltaTime)
{

}

void GameLevel::Draw()
{
    // �� �׸���
    for (auto wall : walls)
    {
        wall->Draw();
    }

    // ���� �׸���

}

bool GameLevel::CheckGameOver()
{
    return false;
}
