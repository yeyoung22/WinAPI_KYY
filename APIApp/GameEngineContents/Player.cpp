#include "Player.h"
#include "Map.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Item.h"
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
	NumberSets.SetOwner(this);
	NumberSets.SetImage("Number.bmp", { 64, 64 }, 10, RGB(255, 0, 255));
	NumberSets.SetValue(static_cast<int>(PlayTimer));

	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		//GameEngineInput::CreateKey("DownMove", 'S');
		//GameEngineInput::CreateKey("UpMove", 'W');
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
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Brake", .ImageName = "Right_Mario.bmp", .Start = 4, .End = 4 });			
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Jump", .ImageName = "Right_Mario.bmp", .Start = 5, .End = 5});
	//	AnimationRender->CreateAnimation({ .AnimationName = "Right_Death", .ImageName = "Right_Mario.bmp", .Start = 6, .End = 6});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Bigger", .ImageName = "Right_Mario.bmp", .Start = 29, .End = 31 });
		

		AnimationRender->CreateAnimation({ .AnimationName = "Death", .ImageName = "Right_Mario.bmp", .Start = 6, .End = 6 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Mario.bmp", .Start = 1, .End = 3 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Brake", .ImageName = "Left_Mario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump", .ImageName = "Left_Mario.bmp", .Start = 5, .End = 5 });
	//	AnimationRender->CreateAnimation({ .AnimationName = "Left_Death", .ImageName = "Left_Mario.bmp", .Start = 6, .End = 6 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Bigger", .ImageName = "Left_Mario.bmp", .Start = 29, .End = 31 });


		//Growth Mario
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthIdle",  .ImageName = "Right_Mario.bmp", .Start = 14, .End = 14 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthMove",  .ImageName = "Right_Mario.bmp", .Start = 15, .End = 17 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthBrake", .ImageName = "Right_Mario.bmp", .Start = 18, .End = 18 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthJump", .ImageName = "Right_Mario.bmp", .Start = 19, .End = 19 });
		
		//역순으로....이미지 재생
		//AnimationRender->CreateAnimation({ .AnimationName = "Right_Smaller", .ImageName = "Right_Mario.bmp", .Start = 6, .End = 6 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthIdle",  .ImageName = "Left_Mario.bmp", .Start = 14, .End = 14 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthMove",  .ImageName = "Left_Mario.bmp", .Start = 15, .End = 17 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthBrake", .ImageName = "Left_Mario.bmp", .Start = 18, .End = 18 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthJump", .ImageName = "Left_Mario.bmp", .Start = 19, .End = 19 });
		//AnimationRender->CreateAnimation({ .AnimationName = "Left_Smaller", .ImageName = "Left_Mario.bmp", .Start = 6, .End = 6 });



		//Fire Mario

		//Star Mario

	}

	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Player);
		BodyCollision->SetScale({ 60, 60 });
	}

	//GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_1.bmp");
	{
		ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_1.bmp");
		
		if (nullptr == ColImage)
		{
			MsgAssert("충돌용 맵 이미지가 없습니다.");
		}

	}

	ChangeState(PlayerState::IDLE);
}

void Player::GravitionalAcc(float _DeltaTime)
{
	if (true == IsGravityOff)
	{
		return;
	}

	float4 Gravity = float4::Down * MoveSpeed * _DeltaTime;
}

bool  Player::MoveCheck(float _DeltaTime)
{
	bool Check = true;
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;					//옮겨갈 위치

	//-----------------다시 만들어야 함---------------------------

	//float4 NextCenterPos = GetPos() + (MoveDir * _Time);						//옮겨 갈 위치(캐릭터의 중간 점)
	////float4 NextLeftPos = NextCenterPos;										//캐릭터의 왼쪽 하단
	//float a = MainPlayer->AnimationRender->GetScale().hx();
	//float4 NextLeftPos = NextCenterPos;
	//NextCenterPos.x - a;

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))	//벽
	{
		Check = false;
		return false;													//허공에 있는 상태
	}

	if (false == Check)
	{
		while (true)													//한 칸씩 위로 올려서 허공이 나오게 함
		{
			MoveDir.y -= 1;												//윈도우 좌표계상에서 위로 올라간 것

			float4 NextPos = GetPos() + MoveDir * _DeltaTime;

			if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
			{
				continue;
			}

			break;
		}
	}

	return true;
}

//void Player::Movecalculation(float _DeltaTime)
//{
//
//
//	float4 PrevPos = GetPos();
//
//	//거리 = 속력*시간(초당 MoveSpeed만큼 픽셀 이동)
//	//시간은 맨 마지막에 SetMove에서 곱해줌
//	MoveDir += float4::Down * MoveSpeed;				//중력가속도
//
//	if (256.0f <= abs(MoveDir.x))						//한계 속도 지정
//	{
//		if (0 >= MoveDir.x)
//		{
//			MoveDir.x = -256.0f;
//		}
//		else
//		{
//			MoveDir.x = 256.0f;
//		}
//	}
//
//
//	//ImageFind에 들어갈 파일명을 변수로 만들어둬야 함
//	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_1.bmp");
//
//
//	if (nullptr == ColImage)
//	{
//		MsgAssert("충돌용 맵 이미지가 없습니다.");
//	}
//
//
//	bool Check = true;
//	float4 NextPos = GetPos() + MoveDir * _DeltaTime;					//옮겨갈 위치
//
//	//-----------------다시 만들어야 함---------------------------
//
//	//float4 NextCenterPos = GetPos() + (MoveDir * _Time);						//옮겨 갈 위치(캐릭터의 중간 점)
//	////float4 NextLeftPos = NextCenterPos;										//캐릭터의 왼쪽 하단
//	//float a = MainPlayer->AnimationRender->GetScale().hx();
//	//float4 NextLeftPos = NextCenterPos;
//	//NextCenterPos.x - a;
//
//	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))	//벽
//	{
//		Check = false;													//허공에 있는 상태
//	}
//
//	if (false == Check)
//	{
//		while (true)													//한 칸씩 위로 올려서 허공이 나오게 함
//		{
//			MoveDir.y -= 1;												//윈도우 좌표계상에서 위로 올라간 것
//
//			float4 NextPos = GetPos() + MoveDir * _DeltaTime;
//
//			if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
//			{
//				continue;
//			}
//
//			break;
//		}
//	}
//
//	SetMove(MoveDir * _DeltaTime);
//}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;										//Level이 바뀌면 MainPlayer는 해당 Level의 Player
}


//디버깅용_벽에 영향을 받지 않고 맵의 끝까지 움직일 수 있음
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
	NumberSets.SetValue(static_cast<int>(PlayTimer));
	PlayTimer -= _DeltaTime;

	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Item), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			ChangeMode(PlayerMode::SUPERMARIO);
			DirCheck("Bigger");
			DirCheck("GrowthIdle");
		}
	}


	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_CirCle, .ThisColType = CT_CirCle }, Collision))
		{
			if (ModeValue == PlayerMode::SUPERMARIO)
			{
				ChangeMode(PlayerMode::MARIO);
				//작아지는 애니메이션 필요함_리버스??------------------------------------
			}
			else
			{
				--Life;
				ChangeState(PlayerState::DEATH);
				//MainPlayer->Death();


				//GameEngineCore::GetInst()->ChangeLevel("EndingLevel");
			}
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
	//Movecalculation(_DeltaTime);
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
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();
	
	//<디버깅용_센터 보기위함>
	Rectangle(DoubleDC,					
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);



	float4 ActPos = GetPos();
	//처음 시작해서 Player가 화면 중에간 오면 카메라가 움직임 시작
	if (ActPos.x >= GameEngineWindow::GetScreenSize().half().x)		
	{
		if (GameEngineInput::IsPress("RightMove"))
		{
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _DeltaTime);
		}

		float4 CameraEndPoint = GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize();

		//if(CameraEndPoint >= GameEngineRender::)
	}


	//Mario Positio 출력
	std::string MarioPosText = "MarioPosition : ";
	MarioPosText += MainPlayer->GetPos().ToString();

	GameEngineLevel::DebugTextPush(MarioPosText);

}