#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	//1�ʸ� ���������� ���� ����
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	Tick = Current.QuadPart - Prev.QuadPart;

	//����ð�
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
