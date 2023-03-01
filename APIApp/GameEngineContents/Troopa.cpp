#include "Troopa.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Troopa::Troopa() 
{
}

Troopa::~Troopa() 
{
}

void Troopa::Start()
{
	{
		AnimationRender = CreateRender(MarioRenderOrder::Monster);
		AnimationRender->SetScale({ 128, 128 });

		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Idle",  .ImageName = "Goomba.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Death",  .ImageName = "Goomba.bmp", .Start = 2, .End = 2 });
		AnimationRender->ChangeAnimation("Goomba_Idle");
	}
	{
		HeadCollision = CreateCollision(MarioCollisionOrder::Monster);
		HeadCollision->SetScale({ 30, 20 });
		HeadCollision->SetPosition({ GetPos().x, GetPos().y - 50 });
	}
	{
		LeftBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		LeftBodyCollision->SetScale({ 10, 45 });
		LeftBodyCollision->SetPosition({ GetPos().x - 20, GetPos().y - 22 });



		//�ϴ� ���� ����
		//LeftBodyCollision->Off();
	}
	{
		RightBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		RightBodyCollision->SetScale({ 10, 45 });
		RightBodyCollision->SetPosition({ GetPos().x + 20, GetPos().y - 22 });
	}

}


void Troopa::Update(float _DeltaTime)
{
	float4 Dir = float4::Left * MoveSpeed * _DeltaTime;
	SetMove(Dir);

	std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();

	std::vector<GameEngineCollision*> Collision;
	if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		&&
		true == PlayerCols[3]->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		)
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			Monster* FindMonster = Collision[i]->GetOwner<Monster>();

			//GameEngineActor* ColActor = Collision[i]->GetActor();

			SetEffectSound("stomp.wav");
			AnimationRender->ChangeAnimation("Goomba_Death");
			Player::TotalScore += Point;
			HeadCollision->Off();
			LeftBodyCollision->Off();
			RightBodyCollision->Off();

			//FindMonster->Death();


		}
	}


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