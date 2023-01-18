#pragma once
// std
#include <list>
#include <string_view>
// 플랫폼
#include <Windows.h>
// User
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 설명 : 장면에 들어갈 요소
class GameEngineLevel;
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;						//GameEngineLevel는 GameEngineActor의 private 멤버도 접근 가능

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline float4 GetPos()
	{
		return Pos;
	}

	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	//이동시킴
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	inline GameEngineLevel* GetLevel()
	{
		return Level;
	}


protected:
	//구현 안 할 수도 있음
	//e.g. 나무: Update를 구현하지 않을 수도 있음

	//시작하기전에 뭔가 준비해야 할 것들
	virtual void Start() {}

	//키입력을 받거나 인공지능을 점수를 계산하거나 하는 것들
	virtual void Update(float _DeltaTime) {}

	//순서를 제어 함수를 한 번 더 실행
	virtual void LateUpdate(float _DeltaTime) {}

	//화면에 그려지는 기능들
	virtual void Render(float _DeltaTime) {}

	inline float GetLiveTime()
	{
		return LiveTime;
	}

private:
	GameEngineLevel* Level;

	int Order;					//업데이트 순서
	float LiveTime = 0.0;
	float4 Pos = { 0.0f, 0.0f };
	
	
	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};
