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
		PipeRender->SetScale({ 160, 296 });


		PipeRender->CreateAnimation({ .AnimationName = "Pipe",  .ImageName = "Pipe.bmp", .Start = 0, .End = 0 });
		PipeRender->CreateAnimation({ .AnimationName = "Left_HorizontalPipe",  .ImageName = "Pipe.bmp", .Start = 1, .End = 1 });
		PipeRender->ChangeAnimation("Pipe");
	}

	{
		
		GateCollision = CreateCollision(MarioCollisionOrder::Item);
		GateCollision->SetScale({ 70, 20 });;
		GateCollision->SetPosition({ GetPos().x, GetPos().y-130});
		
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

			Player::MainPlayer->ChangeState(PlayerState::ENTERPIPE);

			
			float PipeCenterX = GetPos().x;
			float PlayerCurX = Player::MainPlayer->GetPos().x;


			if (PipeCenterX < PlayerCurX)
			{
				Player::MainPlayer->SetMove(float4::Left * MoveSpeed * _DeltaTime);
			}
			else if (PipeCenterX > PlayerCurX)
			{
				Player::MainPlayer->SetMove(float4::Right * MoveSpeed * _DeltaTime);
			}



		}
	}
}
