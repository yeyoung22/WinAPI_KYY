#include "Goomba.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Effect.h"

#include <GameEnginePlatform/GameEngineWindow.h>

Goomba::Goomba() 
{
}

Goomba::~Goomba() 
{
}

void Goomba::Start()
{
	{
		AnimationRender = CreateRender(MarioRenderOrder::Monster);
		AnimationRender->SetScale({ 128, 128 });

		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Idle",  .ImageName = "Goomba.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Death",  .ImageName = "Goomba.bmp", .Start = 2, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Reverse",  .ImageName = "ReverseGoomba.bmp", .Start = 0, .End = 0 });
		AnimationRender->ChangeAnimation("Goomba_Idle");
	}
	{
		HeadCollision = CreateCollision(MarioCollisionOrder::Monster);
		HeadCollision->SetScale({ 30, 20 });
		HeadCollision->SetPosition({ GetPos().x, GetPos().y - 50 });
		HeadCollision->SetDebugRenderType(CT_Rect);
	}
	{
		LeftBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		LeftBodyCollision->SetScale({ 10, 45 });
		LeftBodyCollision->SetPosition({ GetPos().x - 20, GetPos().y - 22 });
		LeftBodyCollision->SetDebugRenderType(CT_Rect);
	}
	{
		RightBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		RightBodyCollision->SetScale({ 10, 45 });
		RightBodyCollision->SetPosition({ GetPos().x + 20, GetPos().y - 22 });
		RightBodyCollision->SetDebugRenderType(CT_Rect);
	}
	{
		TriggerCollision = CreateCollision(MarioCollisionOrder::MonsterTrigger);
		TriggerCollision->SetScale(TriggerScale);
		TriggerCollision->SetPosition(GetPos() + TiriggerCtrlPos);
		TriggerCollision->SetDebugRenderType(CT_Rect);
	}
	{
		PointSet.SetOwner(this);
		PointSet.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		PointSet.SetValue(Point);
		PointSet.SetAlign(Align::Right);
		PointSet.SetRenderPos({ GetPos().x - 26, GetPos().y - 70 });
		PointSet.SetCameraEffect(true);
		PointSet.Off();
	}
}


void Goomba::Update(float _DeltaTime)
{
	std::vector<GameEngineCollision*> Collision;
	
	if (nullptr != TriggerCollision)
	{
		if (true == TriggerCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			MoveStart = true;
			TriggerCollision->Off();
		}
	}
	//trigger와 플레이어가 충돌하면 몬스터가 움직임
	if (true == MoveStart)
	{
		MonsterMove(_DeltaTime);
	}

	if (false == Player::InvincibleMode)
	{	
		//플레이어와 몬스터의 머리 충돌체가 충돌한 경우
		std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();
		if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
			&& true == PlayerCols[4]->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			TimerStart = true;

			SetEffectSound("stomp.wav");
			AnimationRender->ChangeAnimation("Goomba_Death");
			Player::TotalScore += Point;
			HeadCollision->Off();
			LeftBodyCollision->Off();
			RightBodyCollision->Off();


			DeathMon = this;
			StateValue = MonsterState::DEATH;
			return;
		}

		//플레이어와 몬스터의 좌우측 충돌체가 충돌한 경우
		if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
			|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
			)
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				Monster* FindMonster = Collision[i]->GetOwner<Monster>();
				//HeadCollision->Off();
				//LeftBodyCollision->Off();
				//RightBodyCollision->Off();
			}

			if (Player::ModeValue == PlayerMode::SUPERMARIO)
			{
				Player::MainPlayer->SetIsShrinkOn();
				SetEffectSound("pipe.wav");
			}
			else
			{
				--Player::Life;
				Player::MainPlayer->ChangeState(PlayerState::DEATH);
			}

		}
	}

	//플레이어의 공격과 충돌한 경우
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		)
	{
		TimerStart = true;
		for (size_t i = 0; i < Collision.size(); i++)
		{
			Effect* HitAttack = Collision[i]->GetOwner<Effect>();
			HitAttack->Death();

			SetEffectSound("stomp.wav");
			AnimationRender->ChangeAnimation("Goomba_Reverse");

			DeathMon = this;

			IsReverse = true;
			StateValue = MonsterState::DEATH;
			return;
		}
	}

	//Troopa등껍질이랑 충돌한 경우
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Shell), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		|| (true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Shell), .TargetColType = CT_Rect, .ThisColType = CT_Rect })))
	{
		TimerStart = true;

		SetEffectSound("stomp.wav");
		AnimationRender->ChangeAnimation("Goomba_Reverse");
		Player::TotalScore += Point;
		HeadCollision->Off();
		LeftBodyCollision->Off();
		RightBodyCollision->Off();
		
		DeathMon = this;
		IsReverse = true;
		StateValue = MonsterState::DEATH;
		return;
	}

	if (GetLevel()->GetCameraPos().x > GetPos().x)
	{
		Death();
	}
	
}

void Goomba::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

void Goomba::InitGravity(bool _IsGround)
{
	if (true == _IsGround)
	{
		MoveDir.y = 0.0f;
	}
}


bool  Goomba::LiftUp()
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
	//Ground: Player가 서있을 곳(Down)보다 한 칸 아래쪽이 Black이면 땅으로 판단_Player는 Black이 아님
	float4 Down = GetPos();

	if (Black == Player::MainPlayer->ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}


bool Goomba::CheckWall(float4 _Pivot)
{
	float4 CheckPos = GetPos();
	CheckPos += _Pivot;


	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}

bool Goomba::CheckAir()
{
	float4 CheckPos = GetPos();

	if (Magenta == Player::MainPlayer->ColImage->GetPixelColor(CheckPos + float4::Down, Black))
	{
		return true;
	}
	return false;
}

void Goomba::SetTriggerPos(float4 _Pos)
{
	TriggerCollision->SetPosition(_Pos);
}

void Goomba::SetDirSwitch()
{
	if (0.0f > Dir.x)
	{
		Dir = float4::Right;
	}
	else if (0.0f <= Dir.x)
	{
		Dir = float4::Left;
	}

}

void Goomba::SetOnPointSet(int _Point)
{
	PointSet.On();
	PointSet.SetValue(_Point);
}

void Goomba::SetGoombaColOff()
{
	HeadCollision->Off();
	RightBodyCollision->Off();
	LeftBodyCollision->Off();
}

void Goomba::MonsterMove(float _DeltaTime)
{
	switch (StateValue)
	{
	case MonsterState::MOVE:
	{
		MoveUpdate(_DeltaTime);
		break;
	}
	case MonsterState::FALL:
	{
		FallUpdate(_DeltaTime);
		break;
	}
	case MonsterState::DEATH:
	{
		DeathUpdate(_DeltaTime);
		break;
	}
	default:
		break;
	}
}


void Goomba::MoveUpdate(float _DeltaTime)
{

	MoveDir = Dir * MoveSpeed * _DeltaTime;
	SetMove(MoveDir);

	if (true == CheckWall(PivotLPos))
	{
		Dir = float4::Right;
	}

	if (true == CheckWall(PivotRPos))
	{
		Dir = float4::Left;
	}

	//블럭과 충돌한 경우
	std::vector<GameEngineCollision*> Collision;
	if ((false == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		if (true == CheckAir())
		{
			StateValue = MonsterState::FALL;
			return;
		}
	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });

		StateValue = MonsterState::MOVE;
		return;
	}

	if ((false == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		if (true == CheckAir())
		{
			StateValue = MonsterState::FALL;
			return;
		}
	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });

		StateValue = MonsterState::MOVE;
		return;
	}

	//몬스터끼리 충돌한 경우
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			Monster* FindMonster = Collision[i]->GetOwner<Monster>();
		//	FindMonster->SetDirSwitch();
		}
 		SetDirSwitch();

	}
	
	if (true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		SetDirSwitch();
	}
}

void Goomba::FallUpdate(float _DeltaTime)
{

	if ((false == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		AccGravity(_DeltaTime);
		SetMove(Dir * MoveSpeed2 * _DeltaTime);
	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });

		StateValue = MonsterState::MOVE;
		return;
	}


	SetMove(MoveDir * _DeltaTime);

	IsGround = LiftUp();
	InitGravity(IsGround);

	//땅에 닿으면 Idle
	if (true == IsGround)
	{
		StateValue = MonsterState::MOVE;
		return;
	}
}

void Goomba::DeathUpdate(float _DeltaTime)
{
	if (true == IsReverse)
	{
		AccGravity(_DeltaTime);
		SetMove(MoveDir * _DeltaTime);
	}
	

	//AnimationRender->Off();
	SetGoombaColOff();

	SetOnPointSet(Point);




	if (true == TimerStart)
	{
		WaitTime -= _DeltaTime;
		if (0.0f >= WaitTime)
		{
			DeathMon->Death();
			IsReverse = false;
			TimerStart = false;
			WaitTime = 0.3f;
			return;
		}
	}

}




void Goomba::Render(float _DeltaTime)
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