#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
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


// 설명 : 충돌 구조
class CollisionFunctionInit;							//cpp쪽에 구현
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

	// GetOrder로 어떤 충돌 그룹인지 알아야 함
	bool Collision(const CollisionCheckParameter& _CollisionCheck);

	bool Collision(const CollisionCheckParameter& _CollisionCheck, std::vector<GameEngineCollision*>& _Collision);

	void SetOrder(int _Order) override;

	CollisionData GetCollisionData();

	//사각형인지 원형인지 어떤 것으로 호출할지 모르므로 디버깅 할 때 나타날 모양을 직접 세팅
	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

	//CollisionRender 디버깅용
	void DebugRender();


protected:

private:
	//Collision은 내가 원할 때, 원하는 모양으로 충돌시키므로
	//Debug Mode에서는 Debug할때 보는 충돌체 랜더의 타입을 
	//미리 정해줄 필요가 있음
	CollisionType DebugRenderType = CollisionType::CT_CirCle;
};

