#include "QuestionBlock.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"


//QuestionBlock* QuestionBlock::QBlock = nullptr;

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
	BlockCollision->Off();
	
	{
		HeadBlockCollision = CreateCollision(MarioCollisionOrder::Block);
		HeadBlockCollision->SetScale({ 64, 10 });
		HeadBlockCollision->SetPosition({ GetPos().x, GetPos().y - BlockScale + MicroCtrlVert});
		HeadBlockCollision->SetDebugRenderType(CT_Rect);
	}
	{
		LeftBlockCollision = CreateCollision(MarioCollisionOrder::Block);
		LeftBlockCollision->SetScale({ 10, 64 });
		LeftBlockCollision->SetPosition({ GetPos().x - MicroCtrlHorz, GetPos().y - BlockHalfScale });
		LeftBlockCollision->SetDebugRenderType(CT_Rect);
	}
	{
		RightBlockCollision = CreateCollision(MarioCollisionOrder::Block);
		RightBlockCollision->SetScale({ 10, 64 });
		RightBlockCollision->SetPosition({ GetPos().x + MicroCtrlHorz, GetPos().y - BlockHalfScale });
		RightBlockCollision->SetDebugRenderType(CT_Rect);
	}
	{
		BottomBlockCollision = CreateCollision(MarioCollisionOrder::Block);
		BottomBlockCollision->SetScale({ 64, 10 });
		BottomBlockCollision->SetPosition({ GetPos().x, GetPos().y - MicroCtrlVert });
		BottomBlockCollision->SetDebugRenderType(CT_Rect);
	}

	/*HeadBlockCollision->Off();
	LeftBlockCollision->Off();
	RightBlockCollision->Off();
	BottomBlockCollision->Off();*/
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
		MoveDown(_DeltaTime);

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

bool  QuestionBlock::CheckRightBlock()
{
	std::vector<GameEngineCollision*> Collision;
	if (nullptr != RightBlockCollision)
	{
		if (true == RightBlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect}, Collision))
		{
			/*for (size_t i = 0; i < Collision.size(); i++)
			{
				QuestionBlock* FindBlock = Collision[i]->GetOwner<QuestionBlock>();

			}*/
			return true;				//벽
		}

	}
	return false;
}

bool  QuestionBlock::CheckLeftBlock()
{
	std::vector<GameEngineCollision*> Collision;
	if (nullptr != LeftBlockCollision)
	{
		if (true == LeftBlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{

			return true;
		}

	}
	return false;
}

bool  QuestionBlock::CheckBottBlock()
{
	std::vector<GameEngineCollision*> Collision;
	if (nullptr != BottomBlockCollision)
	{
		if (true == BottomBlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{

			return true;
		}

	}
	return false;
}

bool  QuestionBlock::CheckHeadBlock()
{
	std::vector<GameEngineCollision*> Collision;
	if (nullptr != HeadBlockCollision)
	{
		if (true == HeadBlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{

			return true;
		}

	}
	return false;
}


