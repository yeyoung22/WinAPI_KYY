#include "Monster.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Monster::Monster() 
{
}

Monster::~Monster() 
{
}


void Monster::Start()
{
	{
		AnimationRender = CreateRender(MarioRenderOrder::Monster);
		AnimationRender->SetScale({ 128, 128 });

		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Idle",  .ImageName = "Goomba.bmp", .Start = 0, .End = 1 });
		AnimationRender->ChangeAnimation("Goomba_Idle");
	}
	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		BodyCollision->SetScale({ 50, 50 });
		BodyCollision->SetPosition({ GetPos() });
		
		
		
		//�ϴ� ���� ����
		//BodyCollision->Off();
	}
}


void Monster::Update(float _DeltaTime)
{
	float4 Dir = float4::Left * MoveSpeed * _DeltaTime;
	SetMove(Dir);

	//<���ٰ� �״� ����_with Koopa>
	//���� ������� �׾�� ��
	//���ۿ� ������ ����
	//�Ҳɿ� �¾Ƶ� ����
	//�Ӹ��� ������ ����(�������� �ٴ� �浹ü�� �� ������ �¿� �浹ü�� ���̸� ����

	//<Ʈ���� �״� ����>
	//���ٿ� ��κ� ����
	//������ ����� �ִϸ��̼� ����_�� ����
	//�� ���� ������ ������ �������� ���ư�(�⺻�� ������)
	//�����ð����� �� ������ �ٽ� ��Ȱ
	//���ư��ٰ� ���ۿ� ������ ����

	

}