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
	//Role like Wall
	{
		BlockCollision = CreateCollision(MarioCollisionOrder::QBlock);
		BlockCollision->SetScale({ 64, 64 });
		BlockCollision->SetPosition({ GetPos().x, GetPos().y - BlockHalfScale });
		BlockCollision->SetDebugRenderType(CT_Rect);
	}
	{
		HiddenCollision = CreateCollision(MarioCollisionOrder::Hidden);
		HiddenCollision->SetScale({ 64, 64 });
		HiddenCollision->SetPosition({ GetPos().x, GetPos().y - BlockHalfScale });
		HiddenCollision->SetDebugRenderType(CT_Rect);

		HiddenCollision->Off();
	}

	
}

void QuestionBlock::Update(float _DeltaTime)
{
	if (true == IsMove && false == IsUpEnd)
	{
		BlockRender->On();
		MoveUp(_DeltaTime);
	}

	if (true == IsMove && true == IsUpEnd)
	{
		MoveDown(_DeltaTime);
	}


}


void QuestionBlock::MoveUp(float _DeltaTime)
{
	if (0 == StartPos.y)
	{
		StartPos = GetPos();
	}

	MoveDir += float4::Up * MoveSpeed * _DeltaTime;

	SetMove(MoveDir);

	float UpLimit = StartPos.y - UpPower;

	if (UpLimit >= GetPos().y)
	{
		MoveDir = float4::Zero;
		IsUpEnd = true;
		return;
	}
}

void QuestionBlock::MoveDown(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
	SetMove(MoveDir*_DeltaTime);


	if (StartPos.y <= GetPos().y)
	{
		MoveDir = float4::Zero;
		IsMove = false;
		IsUpEnd = false;
		StartPos = float4::Zero;
		return;
	}
}

void QuestionBlock::SetImgChange()
{
	BlockRender->ChangeAnimation("UsedBlock");
}

void QuestionBlock::SetHiddenColOn()
{
	HiddenCollision->On();
	BlockCollision->Off();
}

void QuestionBlock::SetHiddenColOff()
{
	HiddenCollision->Off();
	BlockCollision->On();
}

void QuestionBlock::SetQBlockRenOff()
{
	BlockRender->Off();
}

void QuestionBlock::SetQBlockRenOn()
{
	BlockRender->On();
}