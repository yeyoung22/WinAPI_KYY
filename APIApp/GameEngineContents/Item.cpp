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

		//�ϴ� ������ ����
		//BodyCollision->Off();
	}
	//�⺻������ ����
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
	//Render Img�� �����ϴ� �κ�
	if (PrevItemMode != ItemMode)
	{
		PrevItemMode = ItemMode;

		std::map<ItemType, std::string>::iterator FindIter = AnimNames.find(ItemMode);

		//ã���� �ϴ� ItemMode�� ���� ���
		if (FindIter == AnimNames.end())
		{
			MsgAssert("�������� �ʴ� ItemType(��ȣ)�� Animation�� �������� �߽��ϴ�");
			return;
		}
		ItemRender->ChangeAnimation(FindIter->second);
	}


	if (nullptr != BodyCollision)
	{


		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			//Player�� Coin�� ȹ���� ���(Plyer�� ��� �浹ü�� ������� �浹�� �ϸ� ó���� �͵�)
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
			//������ ���� �ö�
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
			//���� Ÿ�� �������� �̵�
			if (true == IsUpEnd)
			{

				//���� �浹���� ������ �߷��� �������� �ϰ�
				if (false == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
					&& false == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
				{
					MoveDir.x = 0.0f;
					Gravity = 7000.0f;
					AccGravity(_DeltaTime);
					SetMove(MoveDir * _DeltaTime);
				}

				//�������� ����
				if (true == CheckWall(PivotLPos))
				{

					Dir = -Dir;
					return;
				}
				//�������� ����
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

				//�� ���� �ø�
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

	//������ �ƴ��� üũ�ϴ� �κ�
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


//bool ���� ������� ���� ���ؾ� ��------------------------------------------------------
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

	//<������_���� ��������>
	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

	float4 right = GetPos() - GetLevel()->GetCameraPos();
	right += PivotRPos;

	//<������_NextPos ��������>
	Rectangle(DoubleDC,
		right.ix() - 5,
		right.iy() - 5,
		right.ix() + 5,
		right.iy() + 5
	);

	

}