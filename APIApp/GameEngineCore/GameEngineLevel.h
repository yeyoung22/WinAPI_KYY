#pragma once
#include <list>
#include <map>

// ���� : ���
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineLevel						//�߻�Ŭ����
{
	friend GameEngineCore;					//GameEngineCore�� GameEngineLevel�� private ����� ���� ����
	friend GameEngineRender;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;			//���������Լ�

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	/// <summary>
	/// ���͸� ����� �Լ�
	/// </summary>
	/// <typeparam name="ActorType"> GameEngineActor�� ��ӹ��� Ŭ���� Ÿ�� </typeparam>
	/// <param name="_Order"> Actor�� ������Ʈ ���� ���ڰ� �������� ���� ������Ʈ </param>
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);
		
		Actors[_Order].push_back(Actor);	//������ insert �����ϸ� find
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	//�ٸ� ������ ��ü
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	//���ο� ���� ���̴� ����
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:

	//Order�� Actor�� ���� ����
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);
};

