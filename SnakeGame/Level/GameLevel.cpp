#include "GameLevel.h"
#include "string"

GameLevel::GameLevel()
{
    std::string mapString =
        "��������������������������������������������������������������������������������\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��                                      ��\n"
        "��������������������������������������������������������������������������������\n";

    for (char mapChar : mapString)
    {
        int x = 0;
        int y = 0;
        if (mapChar == ' ')
        {
            x++;
            continue;
        }

        if (mapChar == '\n')
        {
            y++;
            continue;
        }
        Wall* wall = new Wall(Vector2(x, y), (const char*)mapChar);
        walls.push_back(wall);
        x++;
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
