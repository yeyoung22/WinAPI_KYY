#include "GameEngineCollision.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"


static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);	//기준: Left


//cpp 내부에만 만듦
class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		//전역이므로 main이 시작되기도 전에 이니셜라이즈
		ColFunctionPtr[CT_CirCle][CT_CirCle] = GameEngineCollision::CollisionCirCleToCirCle;
		ColFunctionPtr[CT_CirCle][CT_Point] = GameEngineCollision::CollisionCirCleToPoint;
		ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
		ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
	}
	~CollisionFunctionInit()
	{

	}
};

//전역으로 하나 선언했으므로 무조건 한 번은 만들어짐
CollisionFunctionInit Init = CollisionFunctionInit();

GameEngineCollision::GameEngineCollision() 
{
}

GameEngineCollision::~GameEngineCollision() 
{
}

bool GameEngineCollision::CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;			
	float Size = Len.Size();								
	float RadiusSum = _Left.Scale.hx();
	return RadiusSum > Size;								
}

bool GameEngineCollision::CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;				//Vec for Right->Left
	float Size = Len.Size();									//Scalar
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();		//r1+r2
	return RadiusSum > Size;									//(r1+r2) > d(중점간의 거리) =  Collision(true)
}

bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Top())							//윈도우 좌표(y: 하단으로 갈수록 증가)
	{
		return false;
	}

	if (_Left.Top() >= _Right.Bot())
	{
		return false;
	}

	if (_Left.Left() >= _Right.Right())							//윈도우 좌표(x: 좌측으로 갈수록 증가)
	{
		return false;
	}

	if (_Left.Right() <= _Right.Left())
	{
		return false;
	}

	return true;
}

bool GameEngineCollision::CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Top() >= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Left() >= _Right.Position.x)
	{
		return false;
	}

	if (_Left.Right() <= _Right.Position.x)
	{
		return false;
	}

	return true;
}

void GameEngineCollision::SetOrder(int _Order)
{
	GetActor()->GetLevel()->PushCollision(this, _Order);
}

//단순히 충돌여부만 알려줌
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	if (false == IsUpdate())
	{
		return false;
	}

	//충돌체를 모아둔 Map에서 Tartget이 되는 대상의 충돌체들의 list를 받아옴
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (OtherCollision == this)
		{
			continue;
		}

		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;						//기준 충돌체 타입
		CollisionType OtherType = _Parameter.TargetColType;					//대상 충돌체 타입

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}

		//충돌 대상이 아무리 많아도 그 중 하나라도 충돌되었다면, true를 반환하는 함수
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}
	//모든 대상과 비교했는데, 충돌이 하나도 발생하지 않으면 false
	return false;
}

//충돌 대상이 하나가 아닌 경우
//For문 돌리기가 편하므로 Vector(&, 외부에서 넣어야 함)
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	if (false == IsUpdate())
	{
		return false;
	}

	_Collision.clear();						//이전에 충돌한 것을 모두 제거하고 새로 집어넣어서 충돌 체크

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;										//충돌을 체크할 당사자
		CollisionType OtherType = _Parameter.TargetColType;									//충돌할 대상

		OtherCollision->SetDebugRenderType(OtherType);										//디버깅 할 때 랜더할 타입 세팅

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}

		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			//충돌한 것을 반환
			_Collision.push_back(OtherCollision);
		}
	}

	//0이 아니면 충돌체가 있음->true
	//0이면 충돌이 없음->false
	return _Collision.size() != 0;
}

CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}


void GameEngineCollision::DebugRender()
{
	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();			//Handle을 이용해 접근
	float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();	//Camera의 영향도 고려
	
	switch (DebugRenderType)															//Switch문으로 타입에 따라 랜더할 모양을 바꿈
	{
	case CT_Point:
		break;
	case CT_CirCle:
	{																					//case에서 지역변수는 영역 안에 선언
		int Radius = GetScale().hix();
		Ellipse(BackBufferDc,															//원형
			DebugRenderPos.ix() - Radius,
			DebugRenderPos.iy() - Radius,
			DebugRenderPos.ix() + Radius,
			DebugRenderPos.iy() + Radius);
		break;
	}
	case CT_Rect:
	{
		Rectangle(BackBufferDc,															//사각형
			DebugRenderPos.ix() - GetScale().hix(),
			DebugRenderPos.iy() - GetScale().hiy(),
			DebugRenderPos.ix() + GetScale().hix(),
			DebugRenderPos.iy() + GetScale().hiy());
		break;
	}
	case CT_Max:
		break;
	default:
		break;
	}
}