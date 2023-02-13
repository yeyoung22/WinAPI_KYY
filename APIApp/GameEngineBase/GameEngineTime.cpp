#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	//1�ʸ� ���������� ���� ����
	//���� ���� ī���� ��(1�ʸ� �� ���� ������ ������ ���)
	QueryPerformanceFrequency(&Second);
	//���� ī������ ���� ��
	QueryPerformanceCounter(&Prev);					//GameEnginTime�� �����Ǹ鼭�� ���� CPU Ŭ�� �� 
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
	QueryPerformanceCounter(&Current);				//���� CPU Ŭ����

	Tick = Current.QuadPart - Prev.QuadPart;		//QuadPart�� ����ü �� ����

	//����ð�
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	Prev.QuadPart = Current.QuadPart;

	//��κ��� �������� double�� �ƴ� float�� ���(float�� ���� �� ���� ����)
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
