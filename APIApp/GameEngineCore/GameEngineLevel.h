#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

// ���� : ���
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject		//�߻�Ŭ����
{
	friend GameEngineCore;							//GameEngineCore�� GameEngineLevel�� private ����� ���� ����
	friend GameEngineRender;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;					//���������Լ�

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;
	
	//���������� ����� ��尡 �ٲ�(On/Off ����ġ)
	static void DebugRenderSwitch()
	{
		IsDebugRender = !IsDebugRender;
	}

	float4 GetMousePos();
	float4 GetMousePosToCamera();

	/// <summary>
	/// ���͸� ����� �Լ�
	/// </summary>
	/// <typeparam name="ActorType"> GameEngineActor�� ��ӹ��� Ŭ���� Ÿ�� </typeparam>
	/// <param name="_Order"> Actor�� ������Ʈ ���� ���ڰ� �������� ���� ������Ʈ </param>
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
		
		Actors[_Order].push_back(Actor);			//������ insert �����ϸ� find

		return dynamic_cast<ActorType*>(Actor);
	}


	//ī�޶� ������
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

		//actor�� ���� �޴� ���� �ƴ� �ش� ������ Ÿ������ ���� �� ����(Monster�����)
		//Actors �׷쿡�� �ʿ��� ���͸� ���� ������, ��Ƽ� ����
		//������ �����Ǿ�� �ϸ�, ���� ������ ���� ����ϹǷ� consst �ƴ�
		//�����ʹ� �ܺη� �Ѱ��ָ� delete�� �� �ִ� ���輺�� ����
		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

			if (nullptr == ConvertType)
			{
				MsgAssert("����Ʈ �Ҽ� ���� ��ȯ�Դϴ�.");
			}

			Result.push_back(ConvertPtr);
		}

		return Result;																//��ȯ: Vector
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

	//TimeScale ����
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
	//�ٸ� ������ ��ü
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;
	//���ο� ���� ���̴� ����
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;

private:
	static bool IsDebugRender;

	float4 CameraPos = float4::Zero;

	static float4 TextOutStart;
	static std::vector<std::string> DebugTexts;

	//Order�� Actor�� ���� ����
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);
	//Level ����Ǹ� ���͵鵵 �Բ� �̵�
	void ActorLevelChangeEnd(GameEngineLevel* _NextLevel);
	void ActorLevelChangeStart(GameEngineLevel* _PrevLevel);


	void ActorStart(GameEngineActor* _Actor, int _Order);

	//map�� ������������ �����ǹǷ� ���� ū ���� ���߿� �����
	std::map<int, std::list<GameEngineRender*>> Renders;
	void PushRender(GameEngineRender* _Render, int _ChangeOrder);

	std::map<int, float> TimeScales;

	std::map<int, std::list<GameEngineCollision*>> Collisions;
	void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);	//Collisio�� Order ���� ����

	void Release();															//���� ����(�ٸ� ������ ���X)
};

