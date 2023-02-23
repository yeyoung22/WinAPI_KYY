#include "Item.h"
#include <vector>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Item::Item() 
{
}

Item::~Item() 
{
}

void Item::Start()
{
	//SuperMushroom
	{
		ItemRender = CreateRender(MarioRenderOrder::Item);
		ItemRender->SetScale({ 128, 128 });


		ItemRender->CreateAnimation({ .AnimationName = "Right_SuperMushroom_Idle",  .ImageName = "Right_SuperMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Right_SuperMushroom_Move",  .ImageName = "Right_SuperMushroom.bmp", .Start = 0, .End = 3 });

		ItemRender->CreateAnimation({ .AnimationName = "Left_SuperMushroom_Idle",  .ImageName = "Left_SuperMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Left_SuperMushroom_Move",  .ImageName = "Left_SuperMushroom.bmp", .Start = 0, .End = 3 });
		
		ItemRender->ChangeAnimation("Left_SuperMushroom_Move");
	}
	//1-UpMushroom
	{
		ItemRender->CreateAnimation({ .AnimationName = "Right_1UPMushroom_Idle",  .ImageName = "Right_1UPMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Right_1UPMushroom_Move",  .ImageName = "Right_1UPMushroom.bmp", .Start = 0, .End = 3 });

		ItemRender->CreateAnimation({ .AnimationName = "Left_1UPMushroom_Idle",  .ImageName = "Left_1UPMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Left_1UPMushroom_Move",  .ImageName = "Left_1UPMushroom.bmp", .Start = 0, .End = 3 });

	}
	//FireFlower
	{
		ItemRender->CreateAnimation({ .AnimationName = "FireFlower_Idle",  .ImageName = "FireFlower.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "FireFlower",  .ImageName = "FireFlower.bmp", .Start = 0, .End = 3 });

	}
	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Item);
		BodyCollision->SetScale({ 60, 60 });;
		BodyCollision->SetPosition({ GetPos().x, GetPos().y - 32 });
	}
}

void Item::Update(float _DeltaTime)
{
	float4 Dir = float4::Left * MoveSpeed * _DeltaTime;

	SetMove(Dir);
	
	std::vector<GameEngineActor*> Items = GetLevel()->GetActors(MarioRenderOrder::Item);


	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			if (Player::ModeValue == PlayerMode::MARIO)
			{
				EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl("growup.wav");
				EffectPlayer.LoopCount(1);
				EffectPlayer.Volume(0.3f);

				Player::MainPlayer->ChangeMode(PlayerMode::SUPERMARIO);
				Player::MainPlayer->DirCheck("Bigger");
			}
			else
			{
				EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl("growup.wav");
				EffectPlayer.LoopCount(1);
				EffectPlayer.Volume(0.3f);
			}


			if (ItemRender->IsAnimationEnd())
			{
				if (false == GameEngineInput::IsAnyKey())
				{
					Player::MainPlayer->ChangeState(PlayerState::IDLE);
				}

				if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
				{
					Player::MainPlayer->ChangeState(PlayerState::MOVE);
				}

				if (GameEngineInput::IsDown("Jump"))
				{
					Player::MainPlayer->ChangeState(PlayerState::JUMP);
				}

				if (GameEngineInput::IsPress("Crouch"))
				{
					Player::MainPlayer->ChangeState(PlayerState::CROUCH);
				}

			}
			ItemRender->Death();
			BodyCollision->Death();

		}
	}

}