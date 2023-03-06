#include "Troopa.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>


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
		AnimationRender->SetScale({ 256, 256 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_TroopaIdle",  .ImageName = "Left_Troopa.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_TroopaShell",  .ImageName = "Left_Troopa.bmp", .Start = 4, .End = 5 });

		AnimationRender->CreateAnimation({ .AnimationName = "Right_TroopaIdle",  .ImageName = "Right_Troopa.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_TroopaShell",  .ImageName = "Right_Troopa.bmp", .Start = 4, .End = 5 });

		AnimationRender->ChangeAnimation("Left_TroopaIdle");
	}
	{
		HeadCollision = CreateCollision(MarioCollisionOrder::Monster);
		HeadCollision->SetScale({ 30, 20 });
		HeadCollision->SetPosition({ GetPos().x, GetPos().y - 52 });
	}
	{
		LeftBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		LeftBodyCollision->SetScale({ 10, 45 });
		LeftBodyCollision->SetPosition({ GetPos().x - 20, GetPos().y - 22 });
	}
	{
		RightBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		RightBodyCollision->SetScale({ 10, 45 });
		RightBodyCollision->SetPosition({ GetPos().x + 20, GetPos().y - 22 });
	}
	{
		LeftShellCollision = CreateCollision(MarioCollisionOrder::Monster);
		LeftShellCollision->SetScale({ 30, 45 });
		LeftShellCollision->SetPosition({ GetPos().x - 12, GetPos().y - 22 });
	}
	{
		RightShellCollision = CreateCollision(MarioCollisionOrder::Monster);
		RightShellCollision->SetScale({ 30, 45 });
		RightShellCollision->SetPosition({ GetPos().x +12, GetPos().y - 22 });
	}
	{
		TriggerCollision = CreateCollision(MarioCollisionOrder::MonsterTrigger);
		TriggerCollision->SetScale(TriggerScale);
		TriggerCollision->SetPosition(GetPos() + TiriggerCtrlPos);
		TriggerCollision->SetDebugRenderType(CT_Rect);
	}

	LeftShellCollision->Off();
	RightShellCollision->Off();

}


void Troopa::Update(float _DeltaTime)
{
	if (nullptr != TriggerCollision)
	{
		if (true == TriggerCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			MoveStart = true;
			TriggerCollision->Off();
		}
	}

	if (true == MoveStart)
	{
		MoveDir = Dir * MoveSpeed * _DeltaTime;
		SetMove(MoveDir);

		if (true == CheckWall(PivotLPos))
		{
			Dir = float4::Right;
			DirCheck("TroopaIdle");
		}

		if (true == CheckWall(PivotRPos))
		{
			Dir = float4::Left;
			DirCheck("TroopaIdle");
		}

		if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Dir = float4::Left;
		}

		if (true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Dir = float4::Right;
		}

	}


	//std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();


	//�÷��̾ �Ӹ��κа� �浹���� ���
	if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		//for (size_t i = 0; i < Collision.size(); i++)
		//{
		//	Monster* FindMonster = Collision[i]->GetOwner<Monster>();

		//	//GameEngineActor* ColActor = Collision[i]->GetActor();

		//	SetEffectSound("stomp.wav");

		//


		//}

		DirCheck("TroopaShell");
		Player::TotalScore += Point;
		HeadCollision->Off();
		LeftBodyCollision->Off();
		RightBodyCollision->Off();
		SetShellColOn();
		//FindMonster->Death();
	}


	//�÷��̾�� ���� �浹ü �� �ϳ��� �浹�� ���
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect } )
		)
	{

			/*HeadCollision->Off();
			LeftBodyCollision->Off();
			RightBodyCollision->Off();*/


		if (false == Player::InvincibleMode)
		{
			if (Player::ModeValue == PlayerMode::SUPERMARIO)
			{
				Player::MainPlayer->SetIsShrinkOn();
				SetEffectSound("pipe.wav");

			}
			else
			{
				--Player::Life;

				Player::MainPlayer->ChangeState(PlayerState::DEATH);


				//GameEngineCore::GetInst()->ChangeLevel("EndingLevel");
			}
		}


	}


	//<Ʈ���� �״� ����>
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

bool Troopa::LiftUp(float4 _Pos)
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


bool Troopa::CheckWall(float4 _Pivot)
{
	float4 CheckPos = GetPos();
	CheckPos += _Pivot;


	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}

void Troopa::SetShellColOn()
{
	LeftShellCollision->On();
	RightShellCollision->On();
}

void Troopa::SetShellColOff()
{
	LeftShellCollision->Off();
	RightShellCollision->Off();
}


void Troopa::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;							//DirString = "Right_"
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

void Troopa::Render(float _DeltaTime)
{
	//float4 PivotRPos = { ImgHalfWidth, -3 };
	//float4 PivotLPos = { -ImgHalfWidth, -3 };

	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();
	ActorPos += PivotLPos;
	//ActorPos.x -= ImgHalfWidth;

	//<������_���� ��������>
	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

	float4 right = GetPos() - GetLevel()->GetCameraPos();
	right += PivotRPos;

	//<������_NextPos ��������>
	Rectangle(DoubleDC,
		right.ix() - 5,
		right.iy() - 5,
		right.ix() + 5,
		right.iy() + 5
	);



}