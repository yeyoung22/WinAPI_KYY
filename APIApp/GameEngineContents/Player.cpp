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
#include "PlayLevel.h"
#include "ContentsUI.h"
#include "EndingBack.h"
#include "QuestionBlock.h"
#include "Brick.h"

//screenSize = {1024, 960}
bool  Player::IsDebugMode = false;
bool Player::InvincibleMode = false;
bool Player::IsUnderGround = false;
Player* Player::MainPlayer;
PlayerMode Player::ModeValue = PlayerMode::MARIO;
float Player::PlayTimer = 400.0f;
int Player::TotalScore = 0;
int Player::NumOfCoin = 0;
int Player::WorldLevel = 1;
int Player::MapLevel = 1;
int Player::TopScore = 0;
int Player::Round = 0;  //0
int Player::Life = 3;
GameEngineImage* Player::ColImage = nullptr;

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
		GameEngineInput::CreateKey("Crouch", 'S');
		//GameEngineInput::CreateKey("Jump", 'W');
		GameEngineInput::CreateKey("Jump", VK_SPACE);			//Mario can jump 5 sec
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Bigger", .ImageName = "Right_Bigger.bmp", .Start = 0, .End = 6, .Loop = false });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Mario.bmp", .Start = 0, .End = 0});
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Mario.bmp", .Start = 1, .End = 3 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Brake", .ImageName = "Left_Mario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump", .ImageName = "Left_Mario.bmp", .Start = 5, .End = 5 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Death", .ImageName = "Left_Mario.bmp", .Start = 6, .End = 6 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hang", .ImageName = "Left_Mario.bmp", .Start = 7, .End = 8 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Bigger", .ImageName = "Left_Bigger.bmp", .Start = 0, .End = 6 , .Loop = false});

		//Growth Mario
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthIdle",  .ImageName = "Right_Mario.bmp", .Start = 14, .End = 14 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthMove",  .ImageName = "Right_Mario.bmp", .Start = 15, .End = 17 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthBrake", .ImageName = "Right_Mario.bmp", .Start = 18, .End = 18 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthJump", .ImageName = "Right_Mario.bmp", .Start = 19, .End = 19 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Crouch", .ImageName = "Right_Mario.bmp", .Start = 20, .End = 20 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GrowthHang", .ImageName = "Right_Mario.bmp", .Start = 21, .End = 22 });
		

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
		AnimationRender->CreateAnimation({ .AnimationName = "Left_FireAttack", .ImageName = "Left_FireMario.bmp", .Start = 20, .End = 20});		
	}
	{
		HeadCollision = CreateCollision(MarioCollisionOrder::Player);
		HeadCollision->SetScale({ 30, 10 });
		HeadCollision->SetPosition({ GetPos().x, GetPos().y - Origin_ColHeight });
		HeadCollision->SetDebugRenderType(CT_Rect);
		
	}
	{
		SHeadCollision = CreateCollision(MarioCollisionOrder::Player);
		SHeadCollision->SetScale({ 30, 10 });
		SHeadCollision->SetPosition({ GetPos().x, GetPos().y - Origin_ColHeight*2 });
		SHeadCollision->SetDebugRenderType(CT_Rect);
	}
	{
		RightBodyCollision = CreateCollision(MarioCollisionOrder::Player);
		RightBodyCollision->SetScale({ 5, 64 });
		RightBodyCollision->SetPosition({ GetPos().x + 24, GetPos().y - 32});
		RightBodyCollision->SetDebugRenderType(CT_Rect);
	}
	{
		LeftBodyCollision = CreateCollision(MarioCollisionOrder::Player);
		LeftBodyCollision->SetScale({ 5, 60 });
		LeftBodyCollision->SetPosition({ GetPos().x - 24, GetPos().y - 32 });
		LeftBodyCollision->SetDebugRenderType(CT_Rect);
	}
	{
		BottomCollision = CreateCollision(MarioCollisionOrder::Player);
		BottomCollision->SetScale({ 38, 10 });
		BottomCollision->SetPosition({ GetPos().x, GetPos().y - 4});
		BottomCollision->SetDebugRenderType(CT_Rect);
	}	

	PlayerCols.push_back(HeadCollision);
	PlayerCols.push_back(SHeadCollision);
	PlayerCols.push_back(RightBodyCollision);
	PlayerCols.push_back(LeftBodyCollision);
	PlayerCols.push_back(BottomCollision);
	ChangeColImage("ColWorld1_1.bmp");

	ChangeState(PlayerState::IDLE);

	AssignLevels(PlayLevel::MapNames, Round);									//Map이랑 World 지정
}


void Player::ChangeColImage(const std::string& _ColMapName)
{
	ColMapName = _ColMapName;
	{
		ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);

		if (nullptr == ColImage)
		{
			MsgAssert("충돌용 맵 이미지가 없습니다.");
		}

	}
}

//Seperate WorldLevel and MapLevel from MapName
void Player::AssignLevels(std::vector<std::vector<int>> _MapNames, int _Round)
{
	WorldLevel = _MapNames[_Round][0];
	MapLevel = _MapNames[_Round][1];
}


void Player::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

void Player::InitGravity(bool _IsGround)
{
	if (true == _IsGround)
	{
		MoveDir.y = 0.0f;
	}
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

			if (true == CheckCeiling(_Pos))
			{
				SetMove(float4::Down);
				return true;
			}

			if (Black == Color)
			{
				SetMove(float4::Up);							//Underground(Black)-> 1 pixel Up
				continue;
			}

			break;
		}

	//땅인지 아닌지 체크하는 부분
	//Ground: Player가 서있을 곳(Down)보다 한 칸 아래쪽이 Black이면 땅으로 판단_Player는 Black이 아님
	float4 Down = GetPos() + _Pos;

	if (Black == ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}


bool Player::CheckWall(float4 _Pos, float4 _Pivot)
{
	float4 CheckPos = GetPos() + _Pos;
	CheckPos += _Pivot;


	if (Black == ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}
	
	return false;
}

bool Player::CheckAir(float4 _Pos)
{
	float4 CheckPos = GetPos() + _Pos;

	if (Magenta == ColImage->GetPixelColor(CheckPos + float4::Down, Black))
	{
		return true;
	}
	return false;
}


bool  Player::CheckCeiling(float4 _Pos)
{	
	float4 CheckPos = GetPos() + _Pos;
	CheckPos.y -= ImgHalfHeight;			//이미지 정중앙에서 위


	if (Black == ColImage->GetPixelColor(CheckPos + float4::Up, Black))
	{
		return true;
	}

	return false;
}




void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;										//When Level is changed,  MainPlayer should be changed this Level's Player

	if (1 == Player::Round)
	{
		float4 PrevMapScale = Map::MainMap->GetMapImgScale(1);
		SetPos({ PrevMapScale.x + 120, GameEngineWindow::GetScreenSize().half().y - 100 });
		GetLevel()->SetCameraPos({ PrevMapScale.x, 0.0f });
	}
	else
	{
		float4 PrevMapScale = Map::MainMap->GetMapImgScale(0);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		SetPos({ 160, StartPos.y - 128 });
		GetLevel()->SetCameraPos(float4::Zero);

		//테스트용 위치 ------------------------------------------------------------지워야 함!!!!!!
		//Player::MainPlayer->SetPos({ 2300, StartPos.y - 128 });					//800
		//SetCameraPos({ Player::MainPlayer->GetPos().x - 200.0f, 0.0f });
	}

	std::vector<std::string> ChangeColName = Map::MainMap->GetColMaps();
	ColImage = nullptr;
	ChangeColImage(ChangeColName[Round]);
	ResetPlayTimer();
	SetPlayerColOn();
	AnimationRender->On();
	ChangeState(PlayerState::IDLE);
	NumOfCoin = 0;
}



void Player::Update(float _DeltaTime)
{
	if (false == TimerStop)
	{
		PlayTimer -= _DeltaTime* TimeSpeed;
	}
	
	//플레이어 모드에 따라 머리 부분 충돌체를 교체
	if (ModeValue == PlayerMode::MARIO && StateValue != PlayerState::DEATH)
	{
		HeadCollision->On();
		SHeadCollision->Off();

		RightBodyCollision->SetScale(MarioColScale);
		LeftBodyCollision->SetScale(MarioColScale);

		if (true == ColLongger)
		{
			RightBodyCollision->SetMove({ 0, ColMoveValue });
			LeftBodyCollision->SetMove({ 0, ColMoveValue });
			ColLongger = false;
		}
	}
	else if(ModeValue != PlayerMode::MARIO && StateValue != PlayerState::DEATH)
	{
		HeadCollision->Off();
		SHeadCollision->On();

		RightBodyCollision->SetScale(SMarioColScale);
		LeftBodyCollision->SetScale(SMarioColScale);

		if (false == ColLongger)
		{
			RightBodyCollision->SetMove({ 0, -ColMoveValue });
			LeftBodyCollision->SetMove({ 0, -ColMoveValue });
			ColLongger = true;
			ColShorter = false;
		}
	}

	if (GetPos().x <= GetLevel()->GetCameraPos().x)							//Mario Can't be to the left of the camera position
	{
		SetPos({ GetLevel()->GetCameraPos().x, GetPos().y });
	}


	if (nullptr != HeadCollision)
	{
		//플레이어의 머리와 QBlock 충돌 체크
		std::vector<GameEngineCollision*> Collision;
		if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
			|| true == SHeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				QuestionBlock* FindBlock = Collision[i]->GetOwner<QuestionBlock>();

				//아이템을 가진 블록은 일단 부딪히면 움직이고 그 다음부터는 움직이지 않음
				if (false == FindBlock->GetIsUsed())
				{
					FindBlock->SetImgChange();
					FindBlock->SetIsUsedOn();					//사용된 블록임을 표시
					FindBlock->IsMoveOn();
				}
				else
				{
					SetEffectSound("bump.wav");
				}
			}
		}

		if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::ItemOn), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
			|| true == SHeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::ItemOn), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				Item* FindItem = Collision[i]->GetOwner<Item>();
				FindItem->SetItemRenderOn();
				FindItem->SetSwitchColOff();
				

				ItemType FindTemType = FindItem->GetItemMode();

				if (FindTemType == ItemType::COIN)
				{
					FindItem->SetBodyColOn();
				}

				if (FindTemType == ItemType::HIDDENCOIN)
				{
					++NumOfCoin;
					TotalScore += Point;

				}

				if (FindTemType != ItemType::HIDDENCOIN && FindTemType != ItemType::LIFEMUSHROOM)
				{
					if (ModeValue == PlayerMode::MARIO)
					{
						FindItem->SetItemMode(ItemType::SUPERMUSHROOM);
					}
					else if (ModeValue == PlayerMode::SUPERMARIO || ModeValue == PlayerMode::FIREMARIO)
					{
						FindItem->SetItemMode(ItemType::FIREFLOWER);
					}
				}

				switch (FindTemType)
				{
				case ItemType::NONE:
					break;
				case ItemType::SUPERMUSHROOM:
				{
					SetEffectSound("vine.wav");
					break;
				}
				case ItemType::LIFEMUSHROOM:
				{
					SetEffectSound("vine.wav");
					break;
				}
				case ItemType::FIREFLOWER:
				{
					SetEffectSound("vine.wav");
					break;
				}
				case ItemType::COIN:
				{
					SetEffectSound("coin.wav");
					break;
				}
				case ItemType::HIDDENCOIN:
				{
					SetEffectSound("coin.wav");
					break;
				}
				default:
					break;
				}
			}
		}
		


		//플레이어의 머리와 Brick 충돌 체크
		if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
			|| true == SHeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				Brick* FindBrick = Collision[i]->GetOwner<Brick>();

				if (ModeValue == PlayerMode::MARIO)
				{
					//마리오이면 벽돌이 움직임
					SetEffectSound("bump.wav");
					FindBrick->IsMoveOn();

					if (false == FindBrick->GetIsSpcBrick())
					{
						//마리오이면 벽돌이 움직임
						SetEffectSound("bump.wav");
						FindBrick->IsMoveOn();
					}
					else
					{
						FindBrick->StartSpcTimerOn();
					}
				}
				else
				{
					if (false == FindBrick->GetIsSpcBrick())
					{
						//그 외는 벽돌이 부서짐
						SetEffectSound("breakblock.wav");
						FindBrick->SetChipOn();

						if (FindBrick->GetIsChipMoveEnd())
						{
							FindBrick->Death();
						}
					}
					else
					{
						FindBrick->SetChipOff();
						FindBrick->StartSpcTimerOn();
					}

				
				}


			}
		}

		if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Hidden), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		|| true == SHeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Hidden), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
  				QuestionBlock* FindQBlock = Collision[i]->GetOwner<QuestionBlock>();
				FindQBlock->SetImgChange();
				FindQBlock->SetQBlockRenOn();
				FindQBlock->SetHiddenColOff();
				FindQBlock->SetIsUsedOn();
			}
		}

	}



	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("DebuggingMode"))
	{
		DebugModeSwitch();
	}

	if (GameEngineInput::IsDown("StageClear"))
	{
		/*if (1 <= Round)
		{
			Round = 2;
			EndingBack::Ending->SetEndingScene(EndingScene::Clear);
			GameEngineCore::GetInst()->ChangeLevel("EndingLevel");

			return;
		}
		else
		{
			++Round;
			std::vector<std::string> ChangeColName = Map::MainMap->GetColMaps();
			ChangeColImage(ChangeColName[Round]);

			AssignLevels(PlayLevel::MapNames, Round);
			PlayLevel::MainPlayLevel->SetBGMStop();
			GameEngineCore::GetInst()->ChangeLevel("OpeningLevel");
			return;
		}*/
		EndingBack::Ending->SetEndingScene(EndingScene::Clear);
		GameEngineCore::GetInst()->ChangeLevel("EndingLevel");
	}



	if (GameEngineInput::IsDown("GoToPipe"))
	{
		MainPlayer->SetPos({ 3500, GameEngineWindow::GetScreenSize().y - 128 });
		GetLevel()->SetCameraPos({GetPos().x, 0});

	}

	
	if (GameEngineInput::IsDown("InvincibleMode"))
	{
		SetInvincibleSwitch();
	}
	
	UpdateState(_DeltaTime);
}

void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;							//DirString = "Right_"
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

	CameraEndPos = Map::SumMapWidth - GameEngineWindow::GetScreenSize().hx();


	if (ActPos.x < CameraEndPos && false == IsUnderGround)
	{
		if (ActPos.x >= CameraPos.x + GameEngineWindow::GetScreenSize().hx())		//Move the camera if Mario is to the right of the center of the screen
		{
			if (GameEngineInput::IsPress("RightMove") || (0 < _Pos.x))
			{
				GetLevel()->SetCameraMove({ _Pos.x, 0 });
			}			
		}
	}
}

void Player::SetEffectSound(const std::string_view& _String, int _loop, float _BasicVolume)
{
	EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String);
	EffectPlayer.LoopCount(_loop);
	EffectPlayer.Volume(_BasicVolume);
}

void Player::Render(float _DeltaTime)
{
	//HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	////Brush를 이용해 색을 채워넣을 수 있음
	//HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	//HBRUSH OldBrush = (HBRUSH)SelectObject(DoubleDC, MyBrush);

	////<디버깅용_센터 보기위함>
	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);

	//SelectObject(DoubleDC, OldBrush);
	//DeleteObject(MyBrush);

	//float4 right = GetPos() - GetLevel()->GetCameraPos();
	//right.x += GetImgHalfWidth() - 8;

	////<디버깅용_NextPos 보기위함>
	//Rectangle(DoubleDC,
	//	right.ix() - 5,
	//	right.iy() - 5,
	//	right.ix() + 5,
	//	right.iy() + 5
	//);

	//float4 left = GetPos() - GetLevel()->GetCameraPos();
	//left.y -= GetImgHalfHeight();


	////<디버깅용_NextPos 보기위함>
	//Rectangle(DoubleDC,
	//	left.ix() - 5,
	//	left.iy() - 5,
	//	left.ix() + 5,
	//	left.iy() + 5
	//);
	
		if (true == IsDebugMode)
		{
			//Mario Positio 출력
			std::string MarioPosText = "MarioPosition : ";
			MarioPosText += MainPlayer->GetPos().ToString();
			GameEngineLevel::DebugTextPush(MarioPosText);

			//Mario StateValue 출력
			std::string MarioStateText = "MarioState : ";
			MarioStateText += MainPlayer->GetStateName();
			GameEngineLevel::DebugTextPush(MarioStateText);

			//InvincibleMode
			std::string MarioInvincibleMode = "Invincible : ";
			if (InvincibleMode)
			{
				MarioInvincibleMode += "true";
			}
			else
			{
				MarioInvincibleMode += "false";
			}
			GameEngineLevel::DebugTextPush(MarioInvincibleMode);
		}

}

void Player::ShrinkEffect(float _DeltaTime)
{
	//Mario Mode Change(Mode Down)
	if (ModeValue == PlayerMode::SUPERMARIO && 2.0f <= InvincibleTimer)
	{
		ChangeMode(PlayerMode::MARIO);
	}
	else if (ModeValue == PlayerMode::FIREMARIO && 2.0f <= InvincibleTimer)
	{
		ChangeMode(PlayerMode::SUPERMARIO);
	}

	InvincibleTimer -= _DeltaTime;

	InvincibleMode = true;
	
	if (true == IsAlphaOn)
	{
		AnimationRender->SetAlpha(150);
	}
	else
	{
		AnimationRender->SetAlpha(255);
	}

	


	if (0.0f >= InvincibleTimer)
	{
		IsShrink = false;
		IsAlphaOn = false;
		AnimationRender->SetAlpha(255);
		InvincibleMode = false;
		InvincibleTimer = 2.0f;
	}
}

void Player::SetPlayerColOff()
{
	HeadCollision->Off();
	SHeadCollision->Off();
	RightBodyCollision->Off();
	LeftBodyCollision->Off();
	BottomCollision->Off();
}

void Player::SetPlayerColOn()
{
	HeadCollision->On();
	SHeadCollision->On();
	RightBodyCollision->On();
	LeftBodyCollision->On();
	BottomCollision->On();
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
			SetMove(float4::Left * FreeSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * FreeSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("RightMove"))
		{
			SetMove(float4::Right * FreeSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * FreeSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("UpMove"))
		{
			SetMove(float4::Up * FreeSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * FreeSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("DownMove"))
		{
			SetMove(float4::Down * FreeSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Down * FreeSpeed * _DeltaTime);
		}
	}
	if (true == FreeMove)
	{
		return true;
	}
	return false;
}
