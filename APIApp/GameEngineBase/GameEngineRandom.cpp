#include "GameEngineRandom.h"
#include <chrono>						//�ð����� ����� ������ �ִ� ���


GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom()
	: MtGen(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))	//�õ尪�� ����ð����� �־���
{
}

GameEngineRandom::~GameEngineRandom()
{
}
