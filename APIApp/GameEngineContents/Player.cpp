#include "Player.h"
#include "Map.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"

 Player* Player::MainPlayer;

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	MainPlayer = this;


	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
		GameEngineInput::CreateKey("Jump", VK_SPACE);			//Mario can jump 5 sec
	
		GameEngineInput::CreateKey("FreeMoveSwitch", '1');
		GameEngineInput::CreateKey("StageClear", '2');
	}

	{
		AnimationRender = CreateRender(MarioRenderOrder::Player);
		AnimationRender->SetScale({ 256, 256 });

		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "Right_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "Right_Mario.bmp", .Start = 1, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Run", .ImageName = "Right_Mario.bmp", .Start = 3, .End = 4 });			//5: jump

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Mario.bmp", .Start = 1, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Run", .ImageName = "Left_Mario.bmp", .Start = 3, .End = 4 });
	}

	ChangeState(PlayerState::IDLE);
}

void Player::Movecalculation(float _DeltaTime)
{
	//거리 = 속력*시간(_DeltaTime을 곱해야 초당 몇 픽셀을 이동)
	MoveDir += float4::Down * MoveSpeed* _DeltaTime;

	if (100.0f <= abs(MoveDir.x))						//절댓값
	{
		if (0 > MoveDir.x)
		{
			GetLevel()->SetCameraMove(float4::Left * 100.0f * _DeltaTime);
			MoveDir.x = -100.0f;
		}
		else {
			GetLevel()->SetCameraMove(float4::Right * 100.0f * _DeltaTime);
			MoveDir.x = 100.0f;
		}
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir.x *= 0.01f;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		//MoveDir += float4::Up * 100.0f * _DeltaTime;

		
	}

	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_1.bmp");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	bool Check = true;
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;			//옮겨갈 위치

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		Check = false;
	}


	if (false == Check)
	{
		while (true)
		{
			MoveDir.y -= 1;

			float4 NextPos = GetPos() + MoveDir * _DeltaTime;

			if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
			{
				continue;
			}

			break;
		}
	}

	SetMove(MoveDir * _DeltaTime);
}

bool FreeMove = false;

bool Player::FreeMoveState(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("FreeMoveSwitch"))
	{
		FreeMove = true;
	}

	if (true == FreeMove)
	{
		if (GameEngineInput::IsPress("LeftMove"))
		{
			SetMove(float4::Left * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * CameraMoveSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("RightMove"))
		{
			SetMove(float4::Right * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * CameraMoveSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("UpMove"))
		{
			SetMove(float4::Up * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * CameraMoveSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("DownMove"))
		{
			SetMove(float4::Down * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Down * CameraMoveSpeed * _DeltaTime);
		}
	}
	if (true == FreeMove)
	{
		return true;
	}
	return false;
}

void Player::Update(float _DeltaTime)
{
	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (GameEngineInput::IsDown("StageClear"))
	{
		
		return;
		//
	}

	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
}

void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

void Player::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos();

	
	//<디버깅용_캐릭터 센터 보기위함>
	Rectangle(DoubleDC,					
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}