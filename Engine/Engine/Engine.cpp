#include "PreCompiledHeader.h"
#include "Engine.h"

// �̱��� ����
Engine* Engine::instance = nullptr;

Engine::Engine()
	:quit(false), screenSize(50, 50)
{
	// ���� �õ� ����
	srand((unsigned int)time(nullptr));

	// �̱��� ��ü ����
	instance = this;

	// �⺻ Ÿ�� ������ �ӵ� ����.
	SetTargetFrameRate(60.0f);

	// ���� ����
	InitializeBuffer();
}


Engine::~Engine()
{
	// ���� ����
	delete[] emptyStringBuffer;
}

void Engine::Run()
{
	// CPU �ð� ���.
	// �ý��� �ð� -> ���ػ� ī����. (10000000).
	// ���κ��忡 �ð谡 ����.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//std::cout << "Frequency: " << frequency.QuadPart << "\n";

	// ���� �ð� �� ���� �ð��� ���� ����.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// ������ ����.
	//float targetFrameRate = 90.0f;

	// �� ������ �ð� ���.
	//float targetOneFrameTime = 1.0f / targetFrameRate;

	// Game-Loop.
	while (true)
	{
		// ���� ����.
		if (quit)
		{
			break;
		}

		// ���� ������ �ð� ����.
		//time = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// ������ �ð� ���.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// �� ������ �ð� ���.
		//float targetOneFrameTime = 1.0f / targetFrameRate;

		// ������ Ȯ��.
		if (deltaTime >= targetOneFrameTime)
		{
			// �Է� ó�� (���� Ű�� ���� ���� Ȯ��).
			ProcessInput();

			// ������Ʈ ������ ���¿����� ������ ������Ʈ ó��.
			if (shouldUpdate)
			{
				Update(deltaTime);
				Draw();
			}

			// Ű ���� ����.
			SavePreviouseKeyStates();

			// ���� ������ �ð� ����.
			previousTime = currentTime;

			// ���� ���� (���� ��û�� ���͵� ����).
			//if (mainLevel)
			//{
			//	//mainLevel->DestroyActor();
			//	mainLevel->ProcessAddedAndDestroyedActor();
			//}

			// ������ Ȱ��ȭ.
			shouldUpdate = true;
		}

		//Sleep(1);
	}
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. Ŀ�� �Ӽ� ����ü ����.
	CONSOLE_CURSOR_INFO info = { };

	// Ÿ�� ���� ����ü �� ����.
	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;

	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;

	}

	// 2. ����.
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x, position.y);
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitGame()
{
	quit = true;
}

Engine& Engine::Get()
{
	// �̱��� ��ü ��ȯ
	return *instance;
}

void Engine::InitializeBuffer()
{
	// ȭ�� ���� �� ����� ���� �ʱ�ȭ.
	// 1. ���� ũ�� �Ҵ�.
	emptyStringBuffer = new char[(screenSize.x + 1) * screenSize.y + 1];

	// ���� �����.
	memset(emptyStringBuffer, ' ', (screenSize.x + 1) * screenSize.y + 1);

	// 2. �� �Ҵ�.
	for (int y = 0; y < screenSize.y; ++y)
	{
		// �� �� ���� ���� ���� �߰�.
		emptyStringBuffer[(y * (screenSize.x + 1)) + screenSize.x] = '\n';
	}

	// �������� �� ���� �߰�.
	emptyStringBuffer[(screenSize.x + 1) * screenSize.y] = '\0';
}

void Engine::ProcessInput()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// Todo: ���� ������Ʈ
}

void Engine::Clear()
{
	// ȭ���� (0,0)���� �̵�.
	SetCursorPosition(0, 0);

	// ȭ�� �����.
	std::cout << emptyStringBuffer;

	// ȭ���� (0,0)���� �̵�.
	SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// Todo: ���� �׸���
}

void Engine::SavePreviouseKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}
