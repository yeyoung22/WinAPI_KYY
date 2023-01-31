#pragma once
// std
#include <list>
#include <string_view>
// �÷���
#include <Windows.h>
// User
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// ���� : ��鿡 �� ���
class GameEngineLevel;
class GameEngineRender;
class GameEngineActor : public GameEngineObject
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

	inline float4 GetPos()
	{
		return Pos;
	}

	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	//�̵���Ŵ
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	GameEngineLevel* GetLevel();


#pragma region CreateRenderEnumOverLoadings

	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));			//enumClass�� ����ȯ �ʿ�
	}
#pragma endregion

	//���� ����
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

protected:
	//���� �� �� ���� ����
	//e.g. ����: Update�� �������� ���� ���� ����

	//�����ϱ����� ���� �غ��ؾ� �� �͵�
	virtual void Start() {}

	//Ű�Է��� �ްų� �ΰ������� ������ ����ϰų� �ϴ� �͵�
	virtual void Update(float _DeltaTime) {}

	//������ ���� �Լ��� �� �� �� ����
	virtual void LateUpdate(float _DeltaTime) {}

	//ȭ�鿡 �׷����� ��ɵ�
	virtual void Render(float _DeltaTime) {}

	inline float GetLiveTime()
	{
		return LiveTime;
	}

private:

	int Order;					//������Ʈ ����
	float LiveTime = 0.0;		//���Ͱ� ����ִ� �ð� ����
	float4 Pos = { 0.0f, 0.0f };
	std::list<GameEngineRender*> RenderList;
	
	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};
