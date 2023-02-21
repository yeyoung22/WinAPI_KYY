#include "GameEngineRandom.h"
#include <chrono>						//시간관련 기능을 제공해 주는 헤더


GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom()
	: MtGen(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))	//시드값을 현재시간으로 넣어줌
{
}

GameEngineRandom::~GameEngineRandom()
{
}
