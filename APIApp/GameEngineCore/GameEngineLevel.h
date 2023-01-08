#pragma once
#include <list>

// ���� : ���
class GameEngineCore;
class GameEngineActor;
class GameEngineLevel						//�߻�Ŭ����
{
	friend GameEngineCore;					//GameEngineCore�� GameEngineLevel�� private ����� ���� ����

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;			//���������Լ�

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};

