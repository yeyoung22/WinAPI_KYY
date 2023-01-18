#pragma once
// std
#include <list>
#include <string_view>
// �÷���
#include <Windows.h>
// User
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// ���� : ��鿡 �� ���
class GameEngineLevel;
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;						//GameEngineLevel�� GameEngineActor�� private ����� ���� ����

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

	//�̵���Ŵ
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	inline GameEngineLevel* GetLevel()
	{
		return Level;
	}


protected:
	//���� �� �� ���� ����
	//e.g. ����: Update�� �������� ���� ���� ����

	//�����ϱ����� ���� �غ��ؾ� �� �͵�
	virtual void Start() {}

	//Ű�Է��� �ްų� �ΰ������� ������ ����ϰų� �ϴ� �͵�
	virtual void Update(float _DeltaTime) {}

	//������ ���� �Լ��� �� �� �� ����
	virtual void LateUpdate(float _DeltaTime) {}

	//ȭ�鿡 �׷����� ��ɵ�
	virtual void Render(float _DeltaTime) {}

	inline float GetLiveTime()
	{
		return LiveTime;
	}

private:
	GameEngineLevel* Level;

	int Order;					//������Ʈ ����
	float LiveTime = 0.0;
	float4 Pos = { 0.0f, 0.0f };
	
	
	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};
