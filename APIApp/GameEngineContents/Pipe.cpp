#include "Pipe.h"
#include <GameEnginePlatform/GameEngineInput.h>
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
		GateCollision = CreateCollision(MarioCollisionOrder::Pipe);
		GateCollision->SetScale({ 70, 20 });;
		GateCollision->SetPosition({ GetPos().x, GetPos().y - 130 });
		GateCollision->SetDebugRenderType(CT_Rect);
	}
	{
		ExitCollision = CreateCollision(MarioCollisionOrder::Pipe);
		ExitCollision->SetScale({ 20, 80 });;
		ExitCollision->SetPosition({ GetPos().x - 66, GetPos().y - 70 });
		ExitCollision->SetDebugRenderType(CT_Rect);
	}

	AnimNames.insert(std::make_pair(PipeType::TOP, "Pipe"));
	AnimNames.insert(std::make_pair(PipeType::LEFT, "Left_HorizontalPipe"));
}

void Pipe::Update(float _DeltaTime)
{
	if (PrevPipeMode != PipeMode)
	{
		PrevPipeMode = PipeMode;

		std::map<PipeType, std::string>::iterator FindIter = AnimNames.find(PipeMode);

		//찾고자 하는 ItemMode가 없는 경우
		if (FindIter == AnimNames.end())
		{
			MsgAssert(static_cast<int>(PipeMode) + "존재하지 않는 PipeType(번호)의 Animation을 가져오려 했습니다");
			return;
		}

		PipeRender->ChangeAnimation(FindIter->second);
	}


	if (nullptr != GateCollision)
	{
		if (true == GameEngineInput::IsPress("DownMove") && true == GateCollision->Collision({.TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect}))
		{
			Player::MainPlayer->ChangeState(PlayerState::ENTERPIPE);

			MoveCenterOnPipe(_DeltaTime);


		}
	}

	if (nullptr != ExitCollision)
	{
		if (true == GameEngineInput::IsPress("RightMove") && true == ExitCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			Player::MainPlayer->ChangeState(PlayerState::ENTERLPIPE);


			



		}
	}
}

void Pipe::MoveCenterOnPipe(float _DeltaTime)
{
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
