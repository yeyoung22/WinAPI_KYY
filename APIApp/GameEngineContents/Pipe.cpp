#include "Pipe.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Pipe::Pipe() 
{
}

Pipe::~Pipe() 
{
}

void Pipe::Start()
{
	{
		PipeRender = CreateRender(MarioRenderOrder::Pipe);
		PipeRender->SetScale({ 128, 128 });


		PipeRender->CreateAnimation({ .AnimationName = "Pipe",  .ImageName = "Pipe.bmp", .Start = 0, .End = 0 });
		PipeRender->CreateAnimation({ .AnimationName = "Left_HorizontalPipe",  .ImageName = "Pipe.bmp", .Start = 1, .End = 1 });
		PipeRender->ChangeAnimation("Pipe");
	}

	{
		
		GateCollision = CreateCollision(MarioCollisionOrder::Item);
		GateCollision->SetScale({ 60, 60 });;
		GateCollision->SetPosition({ GetPos().x, GetPos().y});
		
	}
}

void Pipe::Update(float _DeltaTime)
{
	std::vector<GameEngineActor*> Pipes = GetLevel()->GetActors(MarioRenderOrder::Pipe);


	if (nullptr != GateCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == GateCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			Player::MainPlayer->SetCanMoveOn();
			Player::MainPlayer->DirCheck("Idle");
			Player::MainPlayer->SetMove(float4::Down * _DeltaTime);


			PipeRender->Death();
			GateCollision->Death();

		}
	}
}
