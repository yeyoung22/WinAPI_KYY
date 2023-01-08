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

	template<typename ActorType>
	void CreateActor()
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor);

		Actors.push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

private:
	// ������ �ִ� ������ ��ɿ� ���� �˸� �ȵ�
	//std::list<Player*> Actors;
	//std::list<Monster*> Actors;
	//std::list<Background*> Actors;

	// �ϳ��� �ڷ������� ��� ȭ�鳻�� �����ϴ� �͵��� ǥ��
	std::list<GameEngineActor*> Actors;

	void ActorsUpdate();
	void ActorsRender();


	void ActorStart(GameEngineActor* _Actor);
};

