#pragma once
#include <vector>
#include "GameEngineComponent.h"

enum CollisionType
{
	CT_Point,
	CT_CirCle,
	CT_Rect,
	CT_Max,
};

class CollisionCheckParameter								
{
public:
	int TargetGroup = -342367842;
	CollisionType TargetColType = CollisionType::CT_CirCle;
	CollisionType ThisColType = CollisionType::CT_CirCle;
};

class CollisionData
{
public:
	float4 Position;
	float4 Scale;					//������(R = x)

	float Left() const
	{
		return Position.x - Scale.hx();
	}

	float Right() const
	{
		return Position.x + Scale.hx();
	}

	float Top() const
	{
		return Position.y - Scale.hy();
	}

	float Bot() const
	{
		return Position.y + Scale.hy();
	}
};

// ���� : �浹 ����
class CollisionFunctionInit;							//cpp�ʿ� ����
class GameEngineCollision : public GameEngineComponent
{
	friend CollisionFunctionInit;

public:
	static bool CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right);

	static bool CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right);


public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	// GetOrder�� � �浹 �׷����� �˾ƾ� ��
	bool Collision(const CollisionCheckParameter& _CollisionCheck);

	bool Collision(const CollisionCheckParameter& _CollisionCheck, std::vector<GameEngineCollision*>& _Collision);

	void SetOrder(int _Order) override;

	CollisionData GetCollisionData();

	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

	//CollisionRender ������
	void DebugRender();


protected:

private:
	CollisionType DebugRenderType = CollisionType::CT_CirCle;
};
