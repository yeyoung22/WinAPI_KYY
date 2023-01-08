#pragma once
#include <list>

// 설명 : 장면
class GameEngineCore;
class GameEngineActor;
class GameEngineLevel						//추상클래스
{
	friend GameEngineCore;					//GameEngineCore는 GameEngineLevel의 private 멤버도 접근 가능

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;			//순수가상함수

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};

