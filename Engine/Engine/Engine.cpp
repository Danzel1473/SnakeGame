#include "PreCompiledHeader.h"
#include "Engine.h"

// 싱글톤 선언
Engine* Engine::instance = nullptr;

Engine::Engine()
	:quit(false), screenSize(50, 50)
{
	// 랜덤 시드 설정
	srand((unsigned int)time(nullptr));

	// 싱글톤 객체 설정
	instance = this;

	// 기본 타겟 프레임 속도 설정.
	SetTargetFrameRate(60.0f);

	// 버퍼 설정
	InitializeBuffer();
}


Engine::~Engine()
{
	// 버퍼 삭제
	delete[] emptyStringBuffer;
}

void Engine::Run()
{
	// CPU 시계 사용.
	// 시스템 시계 -> 고해상도 카운터. (10000000).
	// 메인보드에 시계가 있음.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//std::cout << "Frequency: " << frequency.QuadPart << "\n";

	// 시작 시간 및 이전 시간을 위한 변수.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// 프레임 제한.
	//float targetFrameRate = 90.0f;

	// 한 프레임 시간 계산.
	//float targetOneFrameTime = 1.0f / targetFrameRate;

	// Game-Loop.
	while (true)
	{
		// 종료 조건.
		if (quit)
		{
			break;
		}

		// 현재 프레임 시간 저장.
		//time = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// 프레임 시간 계산.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// 한 프레임 시간 계산.
		//float targetOneFrameTime = 1.0f / targetFrameRate;

		// 프레임 확인.
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인).
			ProcessInput();

			// 업데이트 가능한 상태에서만 프레임 업데이트 처리.
			if (shouldUpdate)
			{
				Update(deltaTime);
				Draw();
			}

			// 키 상태 저장.
			SavePreviouseKeyStates();

			// 이전 프레임 시간 저장.
			previousTime = currentTime;

			// 액터 정리 (삭제 요청된 액터들 정리).
			//if (mainLevel)
			//{
			//	//mainLevel->DestroyActor();
			//	mainLevel->ProcessAddedAndDestroyedActor();
			//}

			// 프레임 활성화.
			shouldUpdate = true;
		}

		//Sleep(1);
	}
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. 커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	// 타입 별로 구조체 값 설정.
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

	// 2. 설정.
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
	// 싱글톤 객체 반환
	return *instance;
}

void Engine::InitializeBuffer()
{
	// 화면 지울 때 사용할 버퍼 초기화.
	// 1. 버퍼 크기 할당.
	emptyStringBuffer = new char[(screenSize.x + 1) * screenSize.y + 1];

	// 버퍼 덮어쓰기.
	memset(emptyStringBuffer, ' ', (screenSize.x + 1) * screenSize.y + 1);

	// 2. 값 할당.
	for (int y = 0; y < screenSize.y; ++y)
	{
		// 각 줄 끝에 개행 문자 추가.
		emptyStringBuffer[(y * (screenSize.x + 1)) + screenSize.x] = '\n';
	}

	// 마지막에 널 문자 추가.
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
	// Todo: 레벨 업데이트
}

void Engine::Clear()
{
	// 화면의 (0,0)으로 이동.
	SetCursorPosition(0, 0);

	// 화면 지우기.
	std::cout << emptyStringBuffer;

	// 화면의 (0,0)으로 이동.
	SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// Todo: 레벨 그리기
}

void Engine::SavePreviouseKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}
