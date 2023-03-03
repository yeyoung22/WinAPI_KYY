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
		BlockWallCollision = CreateCollision(MarioCollisionOrder::Block);
		BlockWallCollision->SetScale({ 64, 64 });
		BlockWallCollision->SetPosition({ GetPos().x, GetPos().y - 20 });
		BlockWallCollision->SetDebugRenderType(CT_Rect);
	}

	BlockWallCollision->Off();
}

void Brick::Update(float _DeltaTime)
{

}

