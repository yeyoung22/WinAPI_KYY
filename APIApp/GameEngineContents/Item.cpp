#include "Item.h"
#include <vector>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

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
		
		ItemRender->ChangeAnimation("Left_SuperMushroom_Move");
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

		//일단 아이템 꺼둠
		//BodyCollision->Off();
	}

	AnimNames.insert(std::make_pair(ItemType::SUPERMUSHROOM, "Right_SuperMushroom_Idle"));
	AnimNames.insert(std::make_pair(ItemType::LIFEMUSHROOM, "Right_1UPMushroom_Idle"));
	AnimNames.insert(std::make_pair(ItemType::FIREFLOWER, "FireFlower_Idle"));
	AnimNames.insert(std::make_pair(ItemType::COIN, "Coin"));
	AnimNames.insert(std::make_pair(ItemType::HIDDENCOIN, "HiddenCoin"));
}

void Item::Update(float _DeltaTime)
{
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


	


	/*float4 Dir = float4::Left * MoveSpeed * _DeltaTime;

	SetMove(Dir);*/
	
	std::vector<GameEngineActor*> Items = GetLevel()->GetActors(MarioRenderOrder::Item);


	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			Player::MainPlayer->Player::ChangeState(PlayerState::GROW);

			ItemRender->Death();
			BodyCollision->Death();
		}
	}

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