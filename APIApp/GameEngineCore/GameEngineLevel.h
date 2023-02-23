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
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject		//추상클래스
{
	friend GameEngineCore;							//GameEngineCore는 GameEngineLevel의 private 멤버도 접근 가능
	friend GameEngineRender;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;					//순수가상함수

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;
	
	//누를때마다 디버깅 모드가 바뀜(On/Off 스위치)
	static void DebugRenderSwitch()
	{
		IsDebugRender = !IsDebugRender;
	}

	float4 GetMousePos();
	float4 GetMousePosToCamera();

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


	template<typename ConvertType>
	std::vector<ConvertType*> GetConvertActors(int _GroupIndex)
	{
		std::vector<ConvertType*> Result;

		//actor로 값을 받는 것이 아닌 해당 액터의 타입으로 받을 수 있음(Monster라던가)
		//Actors 그룹에서 필요한 액터만 따로 뽑은뒤, 담아서 리턴
		//원본은 유지되어야 하며, 보통 수정을 위해 사용하므로 consst 아님
		//포인터는 외부로 넘겨주면 delete할 수 있는 위험성이 존재
		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

			if (nullptr == ConvertType)
			{
				MsgAssert("컨버트 할수 없는 변환입니다.");
			}

			Result.push_back(ConvertPtr);
		}

		return Result;																//반환: Vector
	}

	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}
	
	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		std::vector<GameEngineActor*> Result;

		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		return Result;
	}

	static void DebugTextPush(const std::string& _DebugText)
	{
		DebugTexts.push_back(_DebugText);
	}

	//TimeScale 설정
	template<typename EnumType>
	void SetTimeScale(EnumType _GroupIndex, float _Time)
	{
		SetTimeScale(static_cast<int>(_GroupIndex), _Time);
	}

	void SetTimeScale(int _GroupIndex, float _Time)
	{
		TimeScales[_GroupIndex] = _Time;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	//다른 레벨로 교체
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	//새로운 눈에 보이는 레벨
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:
	static bool IsDebugRender;

	float4 CameraPos = float4::Zero;

	static float4 TextOutStart;
	static std::vector<std::string> DebugTexts;

	//Order로 Actor의 순서 관리
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);
	//Level 변경되면 액터들도 함께 이동
	void ActorLevelChangeEnd(GameEngineLevel* _NextLevel);
	void ActorLevelChangeStart(GameEngineLevel* _PrevLevel);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	//map은 오름차순으로 정리되므로 값이 큰 쪽이 나중에 실행됨
	std::map<int, std::list<GameEngineRender*>> Renders;
	void PushRender(GameEngineRender* _Render, int _ChangeOrder);

	std::map<int, float> TimeScales;

	std::map<int, std::list<GameEngineCollision*>> Collisions;
	void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);	//Collisio의 Order 변경 가능

	void Release();															//엔진 수준(다른 곳에서 사용X)
};

