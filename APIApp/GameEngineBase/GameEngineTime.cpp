#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	//1초를 기준으로한 정수 단위
	//현재 성능 카운터 빈도(1초를 몇 번의 정수에 나누어 계산)
	QueryPerformanceFrequency(&Second);
	//성능 카운터의 현재 값
	QueryPerformanceCounter(&Prev);					//GameEnginTime이 생성되면서의 시작 CPU 클럭 수 
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
	QueryPerformanceCounter(&Current);				//종료 CPU 클럭수

	Tick = Current.QuadPart - Prev.QuadPart;		//QuadPart는 구조체 내 정수

	//현재시간
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	Prev.QuadPart = Current.QuadPart;

	//대부분의 엔진에서 double이 아닌 float을 사용(float이 조금 더 연산 빠름)
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
