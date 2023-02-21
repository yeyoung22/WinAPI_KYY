#pragma once
#include <random>

// 설명 : 난수 생성과 관련된 기능
// 난수는 결국 수학적 알고리즘으로 만들어 지며,
// 시드값을 이용해 값을 생성하게 됨
// 시드값이 바뀌지 않으면 같은 값이 나오게 됨
// 보통 여러 개의 랜덤 객체를 만들어서 인터페이스마다 지니고 사용
class GameEngineRandom
{
public:
	//여러 개의 랜덤을 만들 필요X && 하나만 사용하고 싶은 경우에 사용
	static GameEngineRandom MainRandom;
public:
	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	//rand()함수와는 달리 최대, 최소값도 난수 범위에 포함되어 발생

	int RandomInt(int _Min, int _Max)
	{
		//Creater 기능
		std::uniform_int_distribution<int> Uniform(_Min, _Max);		//표현하고 싶은 난수의 최대, 최소값
		return Uniform(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution <float> Uniform(_Min, _Max);
		return Uniform(MtGen);										//함수 객체 문법
	}

	//직접 시드값을 넣어주기 위한 함수
	void SetSeed(__int64 _Seed)
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:

private:
	//랜덤 제너레이터 클래스: 여러 개가 될 수 있음
	std::mt19937_64 MtGen = std::mt19937_64();						//메르센 트위스터 알고리즘을 사용한 제네러이터

	//랜덤 크리에이터 클래스: 1개만 될 수 있음
};

