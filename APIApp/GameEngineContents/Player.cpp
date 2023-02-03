#include "Player.h"
#include "Map.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
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

		//Original Mario
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "Right_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "Right_Mario.bmp", .Start = 1, .End = 3 });
		//Turn되는 시점에서 애니메이션 3, 4 모두인지 4인지 결정해야 함
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Turn", .ImageName = "Right_Mario.bmp", .Start = 4, .End = 4 });			
		
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Jump", .ImageName = "Right_Mario.bmp", .Start = 5, .End = 5});
		AnimationRender->CreateAnimation({ .AnimationName = "Death", .ImageName = "Right_Mario.bmp", .Start = 6, .End = 6});

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Mario.bmp", .Start = 1, .End = 3 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Turn", .ImageName = "Left_Mario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump", .ImageName = "Left_Mario.bmp", .Start = 5, .End = 5 });

	}

	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Player);
		BodyCollision->SetScale({ 60, 60 });
	}

	ChangeState(PlayerState::IDLE);
}

void Player::Movecalculation(float _DeltaTime)
{
	//거리 = 속력*시간(초당 MoveSpeed만큼 픽셀 이동)
	MoveDir += float4::Down * MoveSpeed* _DeltaTime;	//중력가속도

	if (250.0f <= abs(MoveDir.x))						//한계 속도 지정
	{
		if (0 > MoveDir.x)
		{
			if (true == GameEngineInput::IsDown("LeftMove"))
			{
				AnimationRender->ChangeAnimation("Left_Turn");
			}
				MoveDir.x = -250.0f;
		}
		else {
			if (true == GameEngineInput::IsDown("RightMove"))
			{
				AnimationRender->ChangeAnimation("Right_Turn");
			}
				MoveDir.x = 250.0f;
		}
	}



	//좌우키가 안 눌렀으면 멈추게 해야 함
	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir.x *= 0.005f;
	}

	//ImageFind에 들어갈 스트링을 문자열 변수로 만들어둬야 함
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_1.bmp");
	
	if (true == GameEngineInput::IsDown("StageClear"))
	{
		//ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_4.bmp");
	}

	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	bool Check = true;
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;					//옮겨갈 위치

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))	//벽
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
		if (nullptr != BodyCollision)
		{
			BodyCollision->Death();
			BodyCollision = nullptr;
		}

		FreeMove = true;
	}

	if (true == FreeMove)
	{
		if (GameEngineInput::IsPress("LeftMove"))
		{
			SetMove(float4::Left * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("RightMove"))
		{
			SetMove(float4::Right * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("UpMove"))
		{
			SetMove(float4::Up * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * MoveSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("DownMove"))
		{
			SetMove(float4::Down * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Down * MoveSpeed * _DeltaTime);
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
	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_CirCle, .ThisColType = CT_CirCle }, Collision))
		{
			AnimationRender->ChangeAnimation("Death");


			SetMove(float4::Up * _DeltaTime * MoveSpeed);

			//MainPlayer->Death();
		}
	}

	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (GameEngineInput::IsDown("StageClear"))
	{
		Map::MainMap->StageClearOn();
		MainPlayer->SetPos({ 160, GameEngineWindow::GetScreenSize().half().y});
	}

	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
	//Camera(_DeltaTime);
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

//void Player::Camera(float _DeltaTime)
//{
//	if (GameEngineInput::IsPress("LeftMove"))
//	{
//		GetLevel()->SetCameraMove(float4::Left * CameraMoveSpeed * _DeltaTime);
//	}
//	else if (GameEngineInput::IsPress("RightMove"))
//	{
//		GetLevel()->SetCameraMove(float4::Right * CameraMoveSpeed * _DeltaTime);
//	}
//}


void Player::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos();
	ActorPos -= GetLevel()->GetCameraPos();
	
	//<디버깅용_센터 보기위함>
	Rectangle(DoubleDC,					
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);


	float4 ActPos = GetPos();

	if (ActPos.x >= GameEngineWindow::GetScreenSize().half().x)		
	{
		if (GameEngineInput::IsPress("RightMove"))
		{
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _DeltaTime);
		}
	}

}