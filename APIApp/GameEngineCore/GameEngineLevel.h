#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

// 설명 : 장면
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineLevel : public GameEngineObject		//추상클래스
{
	friend GameEngineCore;							//GameEngineCore는 GameEngineLevel의 private 멤버도 접근 가능
	friend GameEngineRender;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;					//순수가상함수

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
	ActorType* CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);
		
		Actors[_Order].push_back(Actor);			//없으면 insert 존재하면 find

		return dynamic_cast<ActorType*>(Actor);
	}

	//카메라 움직임
	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	float4 GetCameraPos()
	{
		return CameraPos;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	//다른 레벨로 교체
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	//새로운 눈에 보이는 레벨
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:
	float4 CameraPos = float4::Zero;

	//Order로 Actor의 순서 관리
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);
};

