#include "Item.h"
#include <vector>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

Item::Item() 
{
}

Item::~Item() 
{
}

void Item::Start()
{
	//SuperMushroom
	{
		ItemRender = CreateRender(MarioRenderOrder::Item);
		ItemRender->SetScale(BasicScale);


		ItemRender->CreateAnimation({ .AnimationName = "Right_SuperMushroom_Idle",  .ImageName = "Right_SuperMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Right_SuperMushroom_Move",  .ImageName = "Right_SuperMushroom.bmp", .Start = 0, .End = 3 });

		ItemRender->CreateAnimation({ .AnimationName = "Left_SuperMushroom_Idle",  .ImageName = "Left_SuperMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Left_SuperMushroom_Move",  .ImageName = "Left_SuperMushroom.bmp", .Start = 0, .End = 3 });
		
		
	}
	//1-UpMushroom
	{
		ItemRender->CreateAnimation({ .AnimationName = "Right_1UPMushroom_Idle",  .ImageName = "Right_1UPMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Right_1UPMushroom_Move",  .ImageName = "Right_1UPMushroom.bmp", .Start = 0, .End = 3 });

		ItemRender->CreateAnimation({ .AnimationName = "Left_1UPMushroom_Idle",  .ImageName = "Left_1UPMushroom.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "Left_1UPMushroom_Move",  .ImageName = "Left_1UPMushroom.bmp", .Start = 0, .End = 3 });

	}
	//FireFlower
	{
		ItemRender->CreateAnimation({ .AnimationName = "FireFlower_Idle",  .ImageName = "FireFlower.bmp", .Start = 0, .End = 0 });
		ItemRender->CreateAnimation({ .AnimationName = "FireFlower",  .ImageName = "FireFlower.bmp", .Start = 0, .End = 3 });

	}
	//Coin
	{
		ItemRender->CreateAnimation({ .AnimationName = "Coin",  .ImageName = "Coin.bmp", .Start = 0, .End = 3 });
	}
	//HiddenCoin
	{
		ItemRender->CreateAnimation({ .AnimationName = "HiddenCoin",  .ImageName = "HiddenCoin.bmp", .Start = 0, .End = 3 });
	}
	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Item);
		BodyCollision->SetScale({ 60, 60 });
		BodyCollision->SetPosition({ GetPos().x, GetPos().y - 32 });
		BodyCollision->SetDebugRenderType(CT_Rect);
	}
	{
		SwitchCollision = CreateCollision(MarioCollisionOrder::ItemOn);
		SwitchCollision->SetScale({ 40, 20 });
		SwitchCollision->SetPosition({ GetPos().x, GetPos().y - 10});
		SwitchCollision->SetDebugRenderType(CT_Rect);

		//일단 아이템 꺼둠
		//BodyCollision->Off();
	}
	//기본적으로 꺼둠
	BodyCollision->Off();
	ItemRender->ChangeAnimation("HiddenCoin");

	AnimNames.insert(std::make_pair(ItemType::SUPERMUSHROOM, "Right_SuperMushroom_Idle"));
	AnimNames.insert(std::make_pair(ItemType::LIFEMUSHROOM, "Right_1UPMushroom_Idle"));
	AnimNames.insert(std::make_pair(ItemType::FIREFLOWER, "FireFlower_Idle"));
	AnimNames.insert(std::make_pair(ItemType::COIN, "Coin"));
	AnimNames.insert(std::make_pair(ItemType::HIDDENCOIN, "HiddenCoin"));
}

void Item::Update(float _DeltaTime)
{
	//Render Img를 변경하는 부분
	if (PrevItemMode != ItemMode)
	{
		PrevItemMode = ItemMode;

		std::map<ItemType, std::string>::iterator FindIter = AnimNames.find(ItemMode);

		//찾고자 하는 ItemMode가 없는 경우
		if (FindIter == AnimNames.end())
		{
			MsgAssert("존재하지 않는 ItemType(번호)의 Animation을 가져오려 했습니다");
			return;
		}
		ItemRender->ChangeAnimation(FindIter->second);
	}


	if (nullptr != BodyCollision)
	{


		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			//Player가 Coin을 획득한 경우(Plyer의 어느 충돌체라도 상관없이 충돌만 하면 처리할 것들)
			if (ItemMode == ItemType::COIN)
			{
				SetEffectSound("coin.wav");
				++Player::MainPlayer->NumOfCoin;
				Player::MainPlayer->TotalScore += Point;
			}
			else if (ItemMode == ItemType::SUPERMUSHROOM)
			{
				Player::MainPlayer->Player::ChangeState(PlayerState::GROW);
				Player::MainPlayer->TotalScore += TPoint;
			}
			else if (ItemMode == ItemType::LIFEMUSHROOM)
			{
				SetEffectSound("1-up.wav");
				++Player::MainPlayer->Life;
				Player::MainPlayer->TotalScore += TPoint;
			}
			else if (ItemMode == ItemType::FIREFLOWER)
			{
				SetEffectSound("growup.wav");
				Player::MainPlayer->ModeValue = PlayerMode::FIREMARIO;
				Player::MainPlayer->TotalScore += TPoint;
			}

			ItemRender->Death();
			BodyCollision->Death();
		}
	}


	if (true == IsSwitchOn)
	{
		WaitTime -= _DeltaTime;

		switch (ItemMode)
		{
		case ItemType::NONE:
			break;
		case ItemType::SUPERMUSHROOM:
		{
			//서서히 위로 올라감
			if (false == IsUpEnd)
			{
				MoveDir += float4::Up * MoveSpeed * _DeltaTime;
				SetMove(float4::Up * MoveSpeed * _DeltaTime);

				if (MoveDir.y <= UpLimit)
				{
					MoveDir = float4::Zero;
					IsUpEnd = true;
					SetBodyColOn();
					return;
				}
			}
			//블럭을 타고 우측으로 이동
			if (true == IsUpEnd)
			{

				//블럭과 충돌하지 않으면 중력의 영향으로 하강
				if (false == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
					&& false == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
				{
					MoveDir.x = 0.0f;
					Gravity = 7000.0f;
					AccGravity(_DeltaTime);
					SetMove(MoveDir * _DeltaTime);
				}

				//좌측벽과 조우
				if (true == CheckWall(PivotLPos))
				{

					Dir = -Dir;
					return;
				}
				//우측벽과 조우
				if (true == CheckWall(PivotRPos))
				{
					Dir = -Dir;
					return;
				}
				if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
				{
					Dir = -Dir;
					MoveDir.x = 0.0f;
				}

				SetMove(Dir * MoveSpeed * _DeltaTime);

				//땅 위로 올림
				LiftUp();
			}




			break;
		}
		case ItemType::LIFEMUSHROOM:
			break;
		case ItemType::FIREFLOWER:
		{
			if (false == IsUpEnd)
			{
				MoveDir += float4::Up * MoveSpeed * _DeltaTime;
				SetMove(float4::Up * MoveSpeed * _DeltaTime);

				if (MoveDir.y <= UpLimit)
				{
					MoveDir = float4::Zero;
					IsUpEnd = true;
					SetBodyColOn();
					ItemRender->ChangeAnimation("FireFlower");
					return;
				}
			}
		
			break;
		}
		case ItemType::COIN:
			break;
		case ItemType::HIDDENCOIN:
		{
			if (false == IsUpEnd)
			{
				MoveDir = float4::Up * JumpPower;
				IsUpEnd = true;
			}

			AccGravity(_DeltaTime);
			SetMove(MoveDir * _DeltaTime);

			if (0 >= WaitTime)
			{
				IsUpEnd = false;

				ItemRender->Death();
				BodyCollision->Death();
			}

			break;
		}
		default:
			break;
		}
	}
}

void Item::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

//bool Item::CheckWall(float4 _Pos, float4 _Pivot)
//{
//	float4 CheckPos = GetPos() + _Pos;
//	CheckPos += _Pivot;
//
//	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
//	{
//		return true;
//	}
//
//	return false;
//}

bool Item::CheckWall(float4 _Pivot)
{
	float4 CheckPos = GetPos();
	CheckPos += _Pivot;

	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}


bool Item::LiftUp()
{
	while (true)
	{
		float4 NextPos = GetPos();

		int Color = Player::MainPlayer->ColImage->GetPixelColor(NextPos, Black);

		if (Black == Color)
		{
			SetMove(float4::Up);							//Underground(Black)-> 1 pixel Up
			continue;
		}

		break;
	}

	//땅인지 아닌지 체크하는 부분
	float4 Down = GetPos();

	if (Black == Player::MainPlayer->ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}


void Item::SetItemRenderScale(float4 _Scale)
{
	ItemRender->SetScale(_Scale);
}

void Item::SetColScale(float4 _Scale)
{
	BodyCollision->SetScale(_Scale);
}

void Item::SetColPos(float4 _Pos)
{
	BodyCollision->SetPosition(_Pos);
}

void Item::CreateItem(float4 _Pos, float4 _Scale, float4 _ColScale, ItemType _Type)
{
	Item* Actor = GetLevel()->CreateActor<Item>(MarioRenderOrder::Item);
	Actor->SetPos(_Pos);
	Actor->SetItemRenderScale(_Scale);
	Actor->SetColScale(_ColScale);
	Actor->SetItemMode(_Type);
}


void Item::SetEffectSound(const std::string_view& _String, int _loop, float _BasicVolume)
{
	EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String);
	EffectPlayer.LoopCount(_loop);
	EffectPlayer.Volume(_BasicVolume);
}

void Item::SetItemRenderOff()
{
	ItemRender->Off();
}

void Item::SetItemRenderOn()
{
	ItemRender->On();
}

void Item::SetBodyColOn()
{
	BodyCollision->On();
}

void Item::SetBodyColOff()
{
	BodyCollision->Off();
}


//bool 값을 사용할지 말지 정해야 함------------------------------------------------------
void Item::SetSwitchColOn()
{
	SwitchCollision->On();
	IsSwitchOn = false;
}

void Item::SetSwitchColOff()
{
	SwitchCollision->Off();
	IsSwitchOn = true;
}

void Item::SetCoinMode()
{
	SwitchCollision->Off();
	SetBodyColOn();
	SetItemRenderOn();
}

void Item::Render(float _DeltaTime)
{
	//float4 PivotRPos = { ImgHalfWidth, -3 };
	//float4 PivotLPos = { -ImgHalfWidth, -3 };

	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();
	ActorPos += PivotLPos;
	//ActorPos.x -= ImgHalfWidth;

	//<디버깅용_센터 보기위함>
	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

	float4 right = GetPos() - GetLevel()->GetCameraPos();
	right += PivotRPos;

	//<디버깅용_NextPos 보기위함>
	Rectangle(DoubleDC,
		right.ix() - 5,
		right.iy() - 5,
		right.ix() + 5,
		right.iy() + 5
	);

	

}