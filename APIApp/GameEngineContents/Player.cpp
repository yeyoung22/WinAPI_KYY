#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Item.h"
#include "Map.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "STLevel.h"
#include "PlayLevel.h"

Player* Player::MainPlayer;
float Player::PlayTimer = 400.0f;

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	ContentsValue::CameraScale = { 1024, 960 };
	
	MainPlayer = this;



	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("Crouch", 'S');
		//GameEngineInput::CreateKey("Jump", 'W');
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Brake", .ImageName = "Right_Mario.bmp", .Start = 4, .End = 4 });			
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Jump", .ImageName = "Right_Mario.bmp", .Start = 5, .End = 5});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Death", .ImageName = "Right_Mario.bmp", .Start = 6, .End = 6});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hang", .ImageName = "Right_Mario.bmp", .Start = 7, .End = 8 });
		//AnimationRender->CreateAnimation({ .AnimationName = "Right_Bigger", .ImageName = "Right_Mario.bmp", .Start = 29, .End = 31 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Bigger", .ImageName = "Right_Bigger.bmp", .Start = 0, .End = 6, .Loop = false });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Mario.bmp", .Start = 1, .End = 3 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Brake", .ImageName = "Left_Mario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump", .ImageName = "Left_Mario.bmp", .Start = 5, .End = 5 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Death", .ImageName = "Left_Mario.bmp", .Start = 6, .End = 6 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hang", .ImageName = "Left_Mario.bmp", .Start = 7, .End = 8 });
		//AnimationRender->CreateAnimation({ .AnimationName = "Left_Bigger", .ImageName = "Left_Mario.bmp", .Start = 29, .End = 31 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Bigger", .ImageName = "Left_Bigger.bmp", .Start = 0, .End = 6 , .Loop = false});

		//Growth Mario
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthIdle",  .ImageName = "Right_Mario.bmp", .Start = 14, .End = 14 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthMove",  .ImageName = "Right_Mario.bmp", .Start = 15, .End = 17 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthBrake", .ImageName = "Right_Mario.bmp", .Start = 18, .End = 18 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthJump", .ImageName = "Right_Mario.bmp", .Start = 19, .End = 19 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Crouch", .ImageName = "Right_Mario.bmp", .Start = 20, .End = 20 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthHang", .ImageName = "Right_Mario.bmp", .Start = 21, .End = 22 });
		
		//역순으로......._GameEngineRender.cpp에 있음
		AnimationRender->CreateReverseAnimation({ .AnimationName = "Right_Smaller", .ImageName = "Right_Mario.bmp", .Start = 31, .End = 29 });
		AnimationRender->CreateReverseAnimation({ .AnimationName = "Left_Smaller", .ImageName = "Left_Mario.bmp",  .Start = 31, .End = 29 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthIdle",  .ImageName = "Left_Mario.bmp", .Start = 14, .End = 14 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthMove",  .ImageName = "Left_Mario.bmp", .Start = 15, .End = 17 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthBrake", .ImageName = "Left_Mario.bmp", .Start = 18, .End = 18 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthJump", .ImageName = "Left_Mario.bmp", .Start = 19, .End = 19 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Crouch", .ImageName = "Left_Mario.bmp", .Start = 20, .End = 20 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GrowthHang", .ImageName = "Left_Mario.bmp", .Start = 21, .End = 22 });
	

		//Fire Mario
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireIdle",  .ImageName = "Right_FireMario.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireMove",  .ImageName = "Right_FireMario.bmp", .Start = 1, .End = 3 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireBrake", .ImageName = "Right_FireMario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireJump", .ImageName = "Right_FireMario.bmp", .Start = 5, .End = 5 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireCrouch", .ImageName = "Right_FireMario.bmp", .Start = 6, .End = 6 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireHang", .ImageName = "Right_FireMario.bmp", .Start = 7, .End = 8 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_FireAttack", .ImageName = "Right_FireMario.bmp", .Start = 20, .End = 20 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireIdle",  .ImageName = "Left_FireMario.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireMove",  .ImageName = "Left_FireMario.bmp", .Start = 1, .End = 3 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireBrake", .ImageName = "Left_FireMario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireJump", .ImageName = "Left_FireMario.bmp", .Start = 5, .End = 5 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireCrouch", .ImageName = "Left_FireMario.bmp", .Start = 6, .End = 6 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireHang", .ImageName = "Left_FireMario.bmp", .Start = 7, .End = 8 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireAttack", .ImageName = "Left_FireMario.bmp", .Start = 20, .End = 20 });

		//Star Mario-----------------------------------------

	}

	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Player);
		BodyCollision->SetScale({ 60, 60 });
		BodyCollision->SetPosition({ GetPos().x, GetPos().y - 32 });
	}

	ColMapName = "ColWorld1_1.bmp";
	{

		ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);
		
		if (nullptr == ColImage)
		{
			MsgAssert("충돌용 맵 이미지가 없습니다.");
		}

	}

	ChangeState(PlayerState::IDLE);
}


void Player::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

//좌우키가 안 눌렀을때 멈추게 할 저항
void  Player::Friction(float4& _Pos, float _DeltaTime)
{
	_Pos.x *= (FrictionPower * _DeltaTime);
}



void Player::LimitSpeed(float4& _Pos)
{
	if (MaxSpeed <= abs(_Pos.x))
	{
		if (0 >= _Pos.x)
		{
			_Pos.x = -MaxSpeed;
		}
		else
		{
			_Pos.x = MaxSpeed;
		}
	}
}





bool  Player::LiftUp(float4 _Pos)
{
	while (true)
	{
		float4 NextPos = GetPos() + _Pos;

		int Color = ColImage->GetPixelColor(NextPos, Black);

		if (Black == Color)
		{
			SetMove(float4::Up);							//Underground(Black)-> 1 pixel Up
			continue;
		}
		break;												//Empty Space(Magenta)->break;
	}


	//함수로 분리할 건지 말건지 정해야 함 -----------------------------------------------------------------
	//땅인지 아닌지 체크하는 부분
	//내가 서있을 곳(Down)보다 한 칸 아래쪽이 검은 색이면 땅으로 판단
	float4 Down = GetPos() + _Pos;

	if (Black == ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}

bool  Player::CheckMove(float4 _Pos, float _DeltaTime)
{
	float4 CheckPos = GetPos() + _Pos*_DeltaTime;


	if (Black == ColImage->GetPixelColor(CheckPos, Black))								//ground, wall
	{
		return false;
	}
	else
	{
		return true;
	}
}


//bool Player::IsWall(float4 _Pos)
//{
//	float4 CheckRPos = GetPos() + _Pos + float4::Right;
//	CheckRPos.x += AnimationRender->GetScale().hx();
//
//	float4 CheckLPos = GetPos() + _Pos + float4::Left;
//	CheckLPos.x -= AnimationRender->GetScale().hx();
//
//	if (0 <= _Pos.x)
//	{
//		if (Black == ColImage->GetPixelColor(CheckRPos, Black))
//		{
//			return true;
//		}
//	}
//
//	if (0 > _Pos.x)
//	{
//		if (Black == ColImage->GetPixelColor(CheckLPos, Black))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}


void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;										//When Level is changed,  MainPlayer should be changed this Level's Player
}


//For Debuging_벽에 영향을 받지 않고 맵의 끝까지 움직일 수 있음
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

	PlayTimer -= _DeltaTime;


	if (GetPos().x <= GetLevel()->GetCameraPos().x)							//Mario Can't be to the left of the camera position
	{
		SetPos({ GetLevel()->GetCameraPos().x, GetPos().y });
	}


	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Item), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			ChangeMode(PlayerMode::SUPERMARIO);
			DirCheck("Bigger");

			if (AnimationRender->IsAnimationEnd())
			{
				if (false == GameEngineInput::IsAnyKey())
				{
					ChangeState(PlayerState::IDLE);
				}

				if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
				{
					ChangeState(PlayerState::MOVE);
				}

				if (GameEngineInput::IsDown("Jump"))
				{
					ChangeState(PlayerState::JUMP);
				}

				if (GameEngineInput::IsPress("Crouch"))
				{
					ChangeState(PlayerState::CROUCH);
				}
			
			}


		}
	}


	if (nullptr != BodyCollision)
	{

		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
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

void Player::Camera(float4 _Pos)
{

	float4 ActPos = GetPos();
	float4 CameraPos = GetLevel()->GetCameraPos();
	float EndPos = PlayLevel::MapScale.x - GameEngineWindow::GetScreenSize().hx();

	if (ActPos.x < EndPos)
	{
		if (ActPos.x >= CameraPos.x + GameEngineWindow::GetScreenSize().hx())						//Move the camera if Mario is to the right of the center of the screen
		{
			if (GameEngineInput::IsPress("RightMove"))
			{
				GetLevel()->SetCameraMove({ _Pos.x, 0 });
			}

		}
	}
}


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


	//Mario Positio 출력
	std::string MarioPosText = "MarioPosition : ";
	MarioPosText += MainPlayer->GetPos().ToString();

	GameEngineLevel::DebugTextPush(MarioPosText);

}