#pragma once
#include <list>
#include <map>

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

	/// <summary>
	/// 액터를 만드는 함수
	/// </summary>
	/// <typeparam name="ActorType"> GameEngineActor를 상속받은 클래스 타입 </typeparam>
	/// <param name="_Order"> Actor의 업데이트 순서 숫자가 작을수록 먼저 업데이트 </param>
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);

		//map은 key로 배열처럼 접근 가능
		Actors[_Order].push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	//다른 레벨로 교체
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	//새로운 눈에 보이는 레벨
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:

	//Order로 Actor의 순서 관리
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);



	void ActorStart(GameEngineActor* _Actor, int _Order);
};

