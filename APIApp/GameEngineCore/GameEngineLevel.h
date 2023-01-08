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
	// 하위에 있는 변수나 기능에 대해 알면 안됨
	//std::list<Player*> Actors;
	//std::list<Monster*> Actors;
	//std::list<Background*> Actors;

	// 하나의 자료형으로 모든 화면내에 등장하는 것들을 표현
	std::list<GameEngineActor*> Actors;

	void ActorsUpdate();
	void ActorsRender();


	void ActorStart(GameEngineActor* _Actor);
};

