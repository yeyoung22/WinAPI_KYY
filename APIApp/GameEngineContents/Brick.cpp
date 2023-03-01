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
}

void Brick::Update(float _DeltaTime)
{

}


void Brick::SetEffectSound(const std::string_view& _String, int _loop, float _BasicVolume)
{
	EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String);
	EffectPlayer.LoopCount(_loop);
	EffectPlayer.Volume(_BasicVolume);
}
