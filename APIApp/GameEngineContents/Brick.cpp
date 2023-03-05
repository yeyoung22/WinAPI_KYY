#include "Brick.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Item.h"

Brick::Brick() 
{
}

Brick::~Brick() 
{
}


void Brick::Start()
{
	{
		BlockRender = CreateRender(MarioRenderOrder::Block);
		BlockRender->SetScale({ 128, 128 });

		BlockRender->CreateAnimation({ .AnimationName = "Brick",  .ImageName = "Brick.bmp", .Start = 0, .End = 0 });
		BlockRender->ChangeAnimation("Brick");
	}
	{
		BlockRender->CreateAnimation({ .AnimationName = "UsedBlock",  .ImageName = "UsedBlock.bmp", .Start = 0, .End = 0 });
	}
	//LeftUp
	{
		Chip1 = CreateRender(MarioRenderOrder::Block);
		Chip1->SetScale(ChipScale);
		Chip1->SetPosition({ GetPos().x - MicroCtrlHorz, GetPos().y - MicroCtrlVert });

		Chip1->CreateAnimation({ .AnimationName = "Left_Chip",  .ImageName = "Chip.bmp", .Start = 0, .End = 0 });
		Chip1->ChangeAnimation("Left_Chip");
	}
	//LeftDown
	{
		Chip2 = CreateRender(MarioRenderOrder::Block);
		Chip2->SetScale(ChipScale);
		Chip2->SetPosition({ GetPos().x - MicroCtrlHorz, GetPos().y - MicroCtrlVert2 });
		Chip2->CreateAnimation({ .AnimationName = "Left_Chip",  .ImageName = "Chip.bmp", .Start = 0, .End = 0 });
		Chip2->ChangeAnimation("Left_Chip");
	}
	//RightUp
	{
		Chip3 = CreateRender(MarioRenderOrder::Block);
		Chip3->SetScale(ChipScale);
		Chip3->SetPosition({ GetPos().x + MicroCtrlHorz, GetPos().y - MicroCtrlVert });

		Chip3->CreateAnimation({ .AnimationName = "Right_Chip",  .ImageName = "Chip.bmp", .Start = 1, .End = 1 });
		Chip3->ChangeAnimation("Right_Chip");
	}
	//RightDown
	{
		Chip4 = CreateRender(MarioRenderOrder::Block);
		Chip4->SetScale(ChipScale);
		Chip4->SetPosition({ GetPos().x + MicroCtrlHorz, GetPos().y - MicroCtrlVert2 });
		Chip4->CreateAnimation({ .AnimationName = "Right_Chip",  .ImageName = "Chip.bmp", .Start = 1, .End = 1 });
		Chip4->ChangeAnimation("Right_Chip");

	}

	//Role like Wall
	{
		BlockCollision = CreateCollision(MarioCollisionOrder::Brick);
		BlockCollision->SetScale({ 64, 64 });
		BlockCollision->SetPosition({ GetPos().x, GetPos().y - BlockHalfScale });
		BlockCollision->SetDebugRenderType(CT_Rect);
	}

	SetChipOff();
}

void Brick::Update(float _DeltaTime)
{

	if (true == IsMove && false == IsUpEnd)
	{
		MoveUp(_DeltaTime);
	}

	if (true == IsMove && true == IsUpEnd)
	{
		MoveDown(_DeltaTime);
	}


	if (true == SpcBrick)
	{
		if (true == StartSpcTimer)
		{
			SpcTimer -= _DeltaTime;
			--Count;
		}


		if (false == IsLast)
		{
			//1_1_Item15(SpcBrick)
			Item* Actor = GetLevel()->CreateActor<Item>(MarioRenderOrder::Item);
			Actor->SetPos({ 6047, 640 });
			Actor->SetItemRenderOff();
		}


		if (0 >= SpcTimer || 0 == Count)
		{
			IsLast = true;
		}

		if (true == IsLast)
		{
			SpcBrick = false;
			BlockRender->ChangeAnimation("UsedBlock");
		}

	}

	if (true == IsChipMove)
	{
		IsChipMoveEnd = false;
		BlockRender->Off();
		WaitTime -= _DeltaTime;

		if (false == IsChipUp)
		{
			ChipMove = float4::Up * JumpPower;
			IsChipUp = true;
		}
		ChipMove += float4::Down * ChipGravity * _DeltaTime;


		SetMove(ChipMove * _DeltaTime);
		
		Chip1->SetMove(float4::Left * ChipSpeed * _DeltaTime);
		Chip2->SetMove(float4::Left * ChipSpeed * _DeltaTime);
		Chip3->SetMove(float4::Right * ChipSpeed * _DeltaTime);
		Chip4->SetMove(float4::Right * ChipSpeed * _DeltaTime);


		if (0 >= WaitTime)
		{
			IsChipUp = false;
			IsChipMoveEnd = true;
			SetChipOff();
			BlockCollision->Death();
		}

	}



}



void Brick::MoveUp(float _DeltaTime)
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

void Brick::MoveDown(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
	SetMove(MoveDir * _DeltaTime);


	if (StartPos.y <= GetPos().y)
	{
		MoveDir = float4::Zero;
		IsMove = false;
		IsUpEnd = false;
		StartPos = float4::Zero;
		return;
	}
}


void Brick::SetChipOff()
{
	IsChipMove = false;

	Chip1->Off();
	Chip2->Off();
	Chip3->Off();
	Chip4->Off();
}

void Brick::SetChipOn()
{
	IsChipMove = true;

	Chip1->On();
	Chip2->On();
	Chip3->On();
	Chip4->On();
}