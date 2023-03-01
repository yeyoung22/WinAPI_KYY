#include "Block.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Block::Block() 
{
}

Block::~Block() 
{
}

void Block::Start()
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


void Block::Update(float _DeltaTime)
{
	std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();



	if (nullptr != BlockCollision)
	{
		//�÷��̾��� �Ӹ��� �ε����� �ϴ� ����� ���Ʒ��� ������
		std::vector<GameEngineCollision*> Collision;
		if (true == BlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
			&&
			true == PlayerCols[0]->Collision({.TargetGroup = static_cast<int>(MarioCollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect}, Collision)
			)
		{
			

			//SetEffectSound("coin.wav");
			BlockRender->ChangeAnimation("UsedBlock");

				
			if (false == IsUp)
			{
				MoveUp(_DeltaTime);
			}
				
			if (true == IsUp && false == IsDown)
			{ 

				MoveDown(_DeltaTime);
			}

			if (true == IsUp && true == IsDown)
			{
				//BlockCollision->Off();
			}

				

			
		}
	}
}

void Block::MoveUp(float _DeltaTime)
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
	IsUp = true;
}

void Block::MoveDown(float _DeltaTime)
{
	//MoveDir.y += BlockSizeHalf;
	
	MoveDir += float4::Down * 300.0f * _DeltaTime;

	SetMove(MoveDir);

	if (GetPos().y >= StartPos.y)
	{
		MoveDir = float4::Zero;
		StartPos = float4::Zero;
		IsDown = true;
		return;
	}


}


void Block::SetEffectSound(const std::string_view& _String, int _loop, float _BasicVolume)
{
	EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String);
	EffectPlayer.LoopCount(_loop);
	EffectPlayer.Volume(_BasicVolume);
}
