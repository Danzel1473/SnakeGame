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

    // �� �ؼ�
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

    // �÷��̾� �߰�
    player = new Player(Vector2((mapString.size() / 17) / 2, 8), this);
    actors.push_back(player);
}

void GameLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    // Todo: �ֱ������� ���� x, y���� ���� random���� 2�� ���ϰ�
    // actor�� ���� ��ȸ�Ͽ� �������� ���� ��ġ�� ���Ͱ� �����ϸ� �ٽ� ���� x,y���� ���Ѵ�.
    // ���Ͱ� ���� ��ġ��� pear ��ü�� �� ��ġ�� �����Ѵ�.

}

void GameLevel::Draw()
{
    // �� �׸���
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
