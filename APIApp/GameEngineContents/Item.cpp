#include "Item.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
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
	{
		AnimationRender = CreateRender(MarioRenderOrder::Item);
		AnimationRender->SetScale({ 128, 128 });


		AnimationRender->CreateAnimation({ .AnimationName = "Right_SuperMushroom_Idle",  .ImageName = "Right_SuperMushroom.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_SuperMushroom_Move",  .ImageName = "Right_SuperMushroom.bmp", .Start = 0, .End = 3 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_SuperMushroom_Idle",  .ImageName = "Left_SuperMushroom.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_SuperMushroom_Move",  .ImageName = "Left_SuperMushroom.bmp", .Start = 0, .End = 3 });
		
		AnimationRender->ChangeAnimation("Left_SuperMushroom_Move");
	}
	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Item);
		BodyCollision->SetScale({ 60, 60 });;
		BodyCollision->SetPosition({ GetPos().x, GetPos().y - 32 });
	}
}

void Item::Update(float _DeltaTime)
{
	/*if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			Player::ChangeMode(PlayerMode::SUPERMARIO);

		}
	}*/

	//
	//float4 Dir = float4::Left * MoveSpeed * _DeltaTime;

	//SetMove(Dir);


}