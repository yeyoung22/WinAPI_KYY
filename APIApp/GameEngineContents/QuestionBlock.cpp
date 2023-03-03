#include "QuestionBlock.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

QuestionBlock::QuestionBlock() 
{
}

QuestionBlock::~QuestionBlock() 
{
}

void QuestionBlock::Start()
{
	{
		BlockRender = CreateRender(MarioRenderOrder::Block);
		BlockRender->SetScale({ 128, 128 });

		BlockRender->CreateAnimation({ .AnimationName = "QuestionBlock",  .ImageName = "QuestionBlock.bmp", .Start = 0, .End = 3 });
		BlockRender->ChangeAnimation("QuestionBlock");
	}
	{
		BlockRender->CreateAnimation({ .AnimationName = "UsedBlock",  .ImageName = "UsedBlock.bmp", .Start = 0, .End = 0 });
	}
	{
		BlockCollision = CreateCollision(MarioCollisionOrder::Block);
		BlockCollision->SetScale({ 64, 10 });
		BlockCollision->SetPosition({ GetPos().x, GetPos().y - 5 });
		BlockCollision->SetDebugRenderType(CT_Rect);
	}

	{
		BlockWallCollision = CreateCollision(MarioCollisionOrder::Block);
		BlockWallCollision->SetScale({ 64, 64 });
		BlockWallCollision->SetPosition({ GetPos().x, GetPos().y - 20 });
		BlockWallCollision->SetDebugRenderType(CT_Rect);
	}
}

void QuestionBlock::Update(float _DeltaTime)
{
	std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();


	if (nullptr != BlockCollision)
	{
		//플레이어의 머리에 부딪히면 일단 블록이 위아래로 움직임
		std::vector<GameEngineCollision*> Collision;
		if (true == BlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
			&&
			true == PlayerCols[0]->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
			)
		{
			TimerStart = true;

			for (size_t i = 0; i < Collision.size(); i++)
			{
				Block* FindBlock = Collision[i]->GetOwner<Block>();

				//SetEffectSound("coin.wav");
				BlockRender->ChangeAnimation("UsedBlock");
				MoveUp();

				BlockCollision->Off();

			}


		}
	}

	if (true == TimerStart)
	{
		WaitTime -= _DeltaTime;
		MoveDown(WaitTime);

		if (0.0f >= WaitTime)
		{
			TimerStart = false;
			WaitTime = 0.3f;
		}
	}
}


void QuestionBlock::MoveUp()
{
	if (0 == StartPos.y)
	{
		StartPos = GetPos();
	}

	float MaxHeight = StartPos.y - BlockSizeHalf;

	MoveDir.y -= BlockSizeHalf;

	SetMove(MoveDir);

	if (GetPos().y <= MaxHeight)
	{
		MoveDir = float4::Zero;
	}
}

void QuestionBlock::MoveDown(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;

	SetMove(MoveDir);

	if (GetPos().y >= StartPos.y)
	{
		MoveDir = float4::Zero;
		StartPos = float4::Zero;
		return;
	}
}






void QuestionBlock::SetEffectSound(const std::string_view& _String, int _loop, float _BasicVolume)
{
	EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String);
	EffectPlayer.LoopCount(_loop);
	EffectPlayer.Volume(_BasicVolume);
}
