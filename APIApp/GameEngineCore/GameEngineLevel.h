#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineDebug.h>
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
	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}
	
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

	//template<typename ConvertType>
	//std::vector<ConvertType*> GetConvertActors(int _GroupIndex)
	//{
	//	std::vector<ConvertType*> Result;

	//	//actor로 값을 받는 것이 아닌 해당 액터의 타입으로 받을 수 있음(Monster라던가)
	//	std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
	//	Result.reserve(Group.size());

	//	for (GameEngineActor* ActorPtr : Group)
	//	{
	//		ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

	//		if (nullptr == ConvertType)
	//		{
	//			MsgAssert("컨버트 할수 없는 변환입니다.");
	//		}

	//		Result.push_back(ConvertPtr);
	//	}

	//	return Result;
	//}

	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}
	
	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		std::vector<GameEngineActor*> Result;

		// 어떤 
		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		return Result;
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

	//map은 오름차순으로 정리되므로 값이 큰 쪽이 나중에 실행됨
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);
};

