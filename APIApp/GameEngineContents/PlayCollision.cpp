#include "PlayCollision.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Item.h"
#include "NumberRenderObjectEX.h"

PlayCollision::PlayCollision() 
{
}

PlayCollision::~PlayCollision() 
{
}



void PlayCollision::Start()
{
	{
		DeadLineCol1 = CreateCollision(MarioCollisionOrder::DeadLine);
		DeadLineCol1->SetScale({ 128, 10 });
		DeadLineCol1->SetPosition({ 4480, 956 });
		DeadLineCol1->SetDebugRenderType(CT_Rect);
	}
	{
		DeadLineCol2 = CreateCollision(MarioCollisionOrder::DeadLine);
		DeadLineCol2->SetScale({ 192, 10 });
		DeadLineCol2->SetPosition({ 5600, 956 });
		DeadLineCol2->SetDebugRenderType(CT_Rect);
	}
	{
		DeadLineCol3 = CreateCollision(MarioCollisionOrder::DeadLine);
		DeadLineCol3->SetScale({ 128, 10 });
		DeadLineCol3->SetPosition({ 9856, 956 });
		DeadLineCol3->SetDebugRenderType(CT_Rect);
	}
	{
		FlagCollision = CreateCollision(MarioCollisionOrder::DeadLine);
		FlagCollision->SetScale({10, 576 });
		FlagCollision->SetPosition({ 12706, 480 });
		FlagCollision->SetDebugRenderType(CT_Rect);
	}
	{
		PointSet.SetOwner(this);
		PointSet.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		PointSet.SetValue(Point);
		PointSet.SetAlign(Align::Right);
		PointSet.SetRenderPos({ GetPos().x, GetPos().y});
		PointSet.SetCameraEffect(true);
		PointSet.Off();
	}
}


void PlayCollision::Update(float _DeltaTime) 
{

	if (nullptr != DeadLineCol1 )
	{

		if ((true == DeadLineCol1->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			|| (true == DeadLineCol2->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			|| (true == DeadLineCol3->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })))
		{
			--Player::Life;
			Player::MainPlayer->ChangeState(PlayerState::DEATH);
		}

		std::vector<GameEngineCollision*> Collision;
		if ((true == DeadLineCol1->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
			|| (true == DeadLineCol2->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
			|| (true == DeadLineCol3->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				Monster* FindMonster = Collision[i]->GetOwner<Monster>();

				FindMonster->Death();
			}
		}

		if ((true == DeadLineCol1->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Item), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
			|| (true == DeadLineCol2->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Item), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
			|| (true == DeadLineCol3->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Item), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				Item* FindItem = Collision[i]->GetOwner<Item>();

				FindItem->Death();
			}
		}
	}

	//플레이어가 깃발(Pole Goal)에 닿은 경우
	if (nullptr != FlagCollision)
	{
		if ((true == FlagCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })))
		{
			if (PlayerState::FALG != Player::MainPlayer->GetPlayerState())
			{
				float4 TouchPoint = Player::MainPlayer->GetPos();
				int TouchPix =TouchPoint.iy();

				
				if (200 < TouchPix && 310 >= TouchPix)
				{
					Point = 4000;
					Player::MainPlayer->TotalScore += Point;
				}
				else if (310 < TouchPix && 410 >= TouchPix)
				{
					Point = 2000;
					Player::MainPlayer->TotalScore += Point;
				}
				else if (410 < TouchPix && 580 >= TouchPix)
				{
					Point = 800;
					Player::MainPlayer->TotalScore += Point;
				}
				else if (580 < TouchPix && 630 >= TouchPix)
				{
					Point = 400;
					Player::MainPlayer->TotalScore += Point;
				}
				else
				{
					Point = 100;
					Player::MainPlayer->TotalScore += Point;
				}
				PointTimerStart = true;
				SetPointSetOn(Point);
				PointSet.SetRenderPos({ TouchPoint.x + 120, TouchPoint.y - 80 });
			}

			FlagCollision->Off();
			Player::MainPlayer->ChangeState(PlayerState::FALG);
		}

	}

	if (true == TimerStart)
	{
		WaitTime -= _DeltaTime;

		if (0.0f >= WaitTime)
		{
			TimerStart = false;
			WaitTime = 0.2f;
		}
	}

	if (true == PointTimerStart)
	{
		PointSetTimer -= _DeltaTime;

		if (0.0f >= PointSetTimer)
		{
			SetPointSetOff();
			PointTimerStart = false;
			PointSetTimer = 0.5f;
		}
	}


	
}


void PlayCollision::SetPointSetOff()
{
	PointSet.Off();
}

void PlayCollision::SetPointSetOn(int _Point)
{
	PointSet.On();
	PointSet.SetValue(_Point);
}