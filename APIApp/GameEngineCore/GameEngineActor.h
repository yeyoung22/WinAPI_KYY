#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

// ���� : ��鿡 �� ���
class GameEngineLevel;
class GameEngineActor
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

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	//�̵���Ŵ
	void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

protected:
	//���� �� �� ���� ����
	//e.g. ����: Update�� �������� ���� ���� ����

	//�����ϱ����� ���� �غ��ؾ� �� �͵�
	virtual void Start() {}

	//Ű�Է��� �ްų� �ΰ������� ������ ����ϰų� �ϴ� �͵�
	virtual void Update() {}

	//ȭ�鿡 �׷����� ��ɵ�
	virtual void Render() {}

private:
	float4 Pos = { 0.0f, 0.0f };
};
