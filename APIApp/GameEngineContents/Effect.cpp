#include "Effect.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player.h"
#include "ContentsEnums.h"


Effect::Effect()
{

}

Effect::~Effect() 
{
}

void Effect::Start()
{
	{
		FireRender = CreateRender(MarioRenderOrder::PlayerAttack);
		FireRender->SetScale({ 128, 128 });

		FireRender->CreateAnimation({ .AnimationName = "Right_Fire",  .ImageName = "Right_Fire.bmp", .Start = 0, .End = 3 });
		FireRender->CreateAnimation({ .AnimationName = "Right_FireHit",  .ImageName = "Right_Fire.bmp", .Start = 4, .End = 6 });

		FireRender->CreateAnimation({ .AnimationName = "Left_Fire",  .ImageName = "Left_Fire.bmp", .Start = 0, .End = 3 });
		FireRender->CreateAnimation({ .AnimationName = "Left_FireHit",  .ImageName = "Right_Fire.bmp", .Start = 4, .End = 6 });
	}
	{
		FireCollision = CreateCollision(MarioCollisionOrder::PlayerAttack);
		FireCollision->SetScale({ 20, 20 });
		FireCollision->SetPosition({ GetPos().x, GetPos().y -16});
		FireCollision->SetDebugRenderType(CT_Rect);
	}

	FireRender->ChangeAnimation("Right_Fire");
}



void Effect::Update(float _DeltaTime)
{
	if (false == IsStop)
	{
		MoveDir += float4::Down * Gravity * _DeltaTime;
		SetMove(MoveDir * _DeltaTime);

		SetMove(Dir * MoveSpeed * _DeltaTime);

		if (true == LiftUp(float4::Zero))
		{
			MoveDir = float4::Up * JumpPower;
		}


		if (true == CheckWall(PivotRPos))
		{
			Dir.x = 0.0f;
			DirCheck("FireHit");

			if (true == FireRender->GameEngineRender::IsAnimationEnd())
			{
				Death();
			}
		}
	}
	

	if (true == FireCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		|| true == FireCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		Death();
	}



}





void Effect::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;							//DirString = "Right_"
	FireRender->ChangeAnimation(DirString + _AnimationName.data());

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
		FireRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}



bool  Effect::LiftUp(float4 _Pos)
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

	//땅인지 아닌지 체크하는 부분
	//Ground: Player가 서있을 곳(Down)보다 한 칸 아래쪽이 Black이면 땅으로 판단_Player는 Black이 아님
	float4 Down = GetPos() + _Pos;

	if (Black == Player::MainPlayer->ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}


bool Effect::CheckWall(float4 _Pivot)
{
	float4 CheckPos = GetPos();
	CheckPos += _Pivot;


	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}