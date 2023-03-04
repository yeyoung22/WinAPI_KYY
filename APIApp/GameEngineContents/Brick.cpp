#include "Brick.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

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
		BlockCollision = CreateCollision(MarioCollisionOrder::Block);
		BlockCollision->SetScale({ 64, 10 });
		BlockCollision->SetPosition({ GetPos().x, GetPos().y - 5 });
		BlockCollision->SetDebugRenderType(CT_Rect);
	}

	{
		HeadBlockCollision = CreateCollision(MarioCollisionOrder::Block);
		HeadBlockCollision->SetScale({ 64, 10 });
		HeadBlockCollision->SetPosition({ GetPos().x, GetPos().y - BlockScale + MicroCtrlVert });
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

}

void Brick::Update(float _DeltaTime)
{

}

