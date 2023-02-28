#include "GameEngineCollision.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"


static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);	//����: Left


//cpp ���ο��� ����
class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		//�����̹Ƿ� main�� ���۵Ǳ⵵ ���� �̴ϼȶ�����
		ColFunctionPtr[CT_CirCle][CT_CirCle] = GameEngineCollision::CollisionCirCleToCirCle;
		ColFunctionPtr[CT_CirCle][CT_Point] = GameEngineCollision::CollisionCirCleToPoint;
		ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
		ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
	}
	~CollisionFunctionInit()
	{

	}
};

//�������� �ϳ� ���������Ƿ� ������ �� ���� �������
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
	return RadiusSum > Size;									//(r1+r2) > d(�������� �Ÿ�) =  Collision(true)
}

bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Top())							//������ ��ǥ(y: �ϴ����� ������ ����)
	{
		return false;
	}

	if (_Left.Top() >= _Right.Bot())
	{
		return false;
	}

	if (_Left.Left() >= _Right.Right())							//������ ��ǥ(x: �������� ������ ����)
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

//�ܼ��� �浹���θ� �˷���
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	if (false == IsUpdate())
	{
		return false;
	}

	//�浹ü�� ��Ƶ� Map���� Tartget�� �Ǵ� ����� �浹ü���� list�� �޾ƿ�
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

		CollisionType Type = _Parameter.ThisColType;						//���� �浹ü Ÿ��
		CollisionType OtherType = _Parameter.TargetColType;					//��� �浹ü Ÿ��

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("���� �浹�Լ��� ������ ���� �浹 Ÿ���Դϴ�");
		}

		//�浹 ����� �ƹ��� ���Ƶ� �� �� �ϳ��� �浹�Ǿ��ٸ�, true�� ��ȯ�ϴ� �Լ�
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}
	//��� ���� ���ߴµ�, �浹�� �ϳ��� �߻����� ������ false
	return false;
}

//�浹 ����� �ϳ��� �ƴ� ���
//For�� �����Ⱑ ���ϹǷ� Vector(&, �ܺο��� �־�� ��)
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	if (false == IsUpdate())
	{
		return false;
	}

	_Collision.clear();						//������ �浹�� ���� ��� �����ϰ� ���� ����־ �浹 üũ

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;										//�浹�� üũ�� �����
		CollisionType OtherType = _Parameter.TargetColType;									//�浹�� ���

		OtherCollision->SetDebugRenderType(OtherType);										//����� �� �� ������ Ÿ�� ����

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("���� �浹�Լ��� ������ ���� �浹 Ÿ���Դϴ�");
		}

		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			//�浹�� ���� ��ȯ
			_Collision.push_back(OtherCollision);
		}
	}

	//0�� �ƴϸ� �浹ü�� ����->true
	//0�̸� �浹�� ����->false
	return _Collision.size() != 0;
}

CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}


void GameEngineCollision::DebugRender()
{
	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();			//Handle�� �̿��� ����
	float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();	//Camera�� ���⵵ ���
	
	switch (DebugRenderType)															//Switch������ Ÿ�Կ� ���� ������ ����� �ٲ�
	{
	case CT_Point:
		break;
	case CT_CirCle:
	{																					//case���� ���������� ���� �ȿ� ����
		int Radius = GetScale().hix();
		Ellipse(BackBufferDc,															//����
			DebugRenderPos.ix() - Radius,
			DebugRenderPos.iy() - Radius,
			DebugRenderPos.ix() + Radius,
			DebugRenderPos.iy() + Radius);
		break;
	}
	case CT_Rect:
	{
		Rectangle(BackBufferDc,															//�簢��
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