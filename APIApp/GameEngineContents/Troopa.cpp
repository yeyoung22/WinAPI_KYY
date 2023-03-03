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


void Troopa::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

void Troopa::InitGravity(bool _IsGround)
{
	if (true == _IsGround)
	{
		MoveDir.y = 0.0f;
	}
}

//�¿�Ű�� �� �������� ���߰� �� ����
void  Troopa::Friction(float4& _Pos, float _DeltaTime)
{
	_Pos.x *= (FrictionPower * _DeltaTime);
}

bool  Troopa::LiftUp(float4 _Pos)
{
	while (true)
	{
		float4 NextPos = GetPos() + _Pos;

		int Color = Player::MainPlayer->ColImage->GetPixelColor(NextPos, Black);

		if (Black == Color)
		{
			SetMove(float4::Up);							//Underground(Black)-> 1 pixel Up
			continue;
		}

		break;
	}

	//������ �ƴ��� üũ�ϴ� �κ�
	//Ground: Player�� ������ ��(Down)���� �� ĭ �Ʒ����� Black�̸� ������ �Ǵ�_Player�� Black�� �ƴ�
	float4 Down = GetPos() + _Pos;

	if (Black == Player::MainPlayer->ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}


bool Troopa::CheckWall(float4 _Pos, float4 _Pivot)
{
	float4 CheckPos = GetPos() + _Pos;
	CheckPos += _Pivot;


	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}