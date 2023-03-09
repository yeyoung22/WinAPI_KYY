#include "Troopa.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Effect.h"
#include "Goomba.h"

#include <GameEnginePlatform/GameEngineWindow.h>


Troopa::Troopa() 
{
}

Troopa::~Troopa() 
{
}

void Troopa::Start()
{
	{
		AnimationRender = CreateRender(MarioRenderOrder::Monster);
		AnimationRender->SetScale({ 256, 256 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_TroopaIdle",  .ImageName = "Left_Troopa.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_TroopaShell",  .ImageName = "Left_Troopa.bmp", .Start = 4, .End = 5 });

		AnimationRender->CreateAnimation({ .AnimationName = "Right_TroopaIdle",  .ImageName = "Right_Troopa.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_TroopaShell",  .ImageName = "Right_Troopa.bmp", .Start = 4, .End = 5 });

		AnimationRender->ChangeAnimation("Left_TroopaIdle");
	}
	{
		HeadCollision = CreateCollision(MarioCollisionOrder::Monster);
		HeadCollision->SetScale({ 30, 20 });
		HeadCollision->SetPosition({ GetPos().x, GetPos().y - 52 });
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
		LeftShellCollision = CreateCollision(MarioCollisionOrder::Shell);
		LeftShellCollision->SetScale({ 30, 45 });
		LeftShellCollision->SetPosition({ GetPos().x - 12, GetPos().y - 22 });
		LeftShellCollision->SetDebugRenderType(CT_Rect);
	}
	{
		RightShellCollision = CreateCollision(MarioCollisionOrder::Shell);
		RightShellCollision->SetScale({ 30, 45 });
		RightShellCollision->SetPosition({ GetPos().x +12, GetPos().y - 22 });
		RightShellCollision->SetDebugRenderType(CT_Rect);
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
		PointSet.SetRenderPos({ GetPos().x, GetPos().y - 70 });
		PointSet.SetCameraEffect(true);
		PointSet.Off();
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
	LeftShellCollision->Off();
	RightShellCollision->Off();

}


void Troopa::Update(float _DeltaTime)
{
	if (nullptr != TriggerCollision)
	{
		if (true == TriggerCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			MoveStart = true;
			TriggerCollision->Off();
		}
	}

	if (true == MoveStart)
	{
		MonsterMove(_DeltaTime);
	}


	//std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();


	//플레이어가 머리부분과 충돌했을 경우
	if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		SetEffectSound("stomp.wav");
		//Player::TotalScore += Point;

		HeadCollision->Off();
		LeftBodyCollision->Off();
		RightBodyCollision->Off();

		StateValue = MonsterState::IDLE;
		return;
	}


	//플레이어와 양쪽 충돌체 중 하나가 충돌한 경우
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect } )
		)
	{

		if (false == Player::InvincibleMode)
		{
			if (Player::ModeValue == PlayerMode::SUPERMARIO || Player::ModeValue == PlayerMode::FIREMARIO)
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
	std::vector<GameEngineCollision*> Collision;
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		)
	{
		TimerStart = true;
		for (size_t i = 0; i < Collision.size(); i++)
		{
			Effect* HitAttack = Collision[i]->GetOwner<Effect>();
			HitAttack->Death();
			Player::MainPlayer->TotalScore += Point;

			SetEffectSound("stomp.wav");
			DirCheck("TroopaShell");

			DeathMon = this;

			StateValue = MonsterState::DEATH;
			return;
		}
	}

	//구멍에 빠진 경우, Death
	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::DeadLine), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::DeadLine), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		)
	{
		Player::MainPlayer->TotalScore += Point;
		Death();
	}
	if (true == RightShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::DeadLine), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		|| true == LeftShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::DeadLine), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		)
	{
		Player::MainPlayer->TotalScore += Point;
		Death();
	}

	if (StateValue == MonsterState::IDLE)
	{
		ShellColOffTime -= _DeltaTime;

		if (0.0f >= ShellColOffTime)
		{
			ShellColOffTime = 1.0f;
			SetShellColOn();
		}
	}
	
}


void Troopa::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

void Troopa::InitGravity(bool _IsGround)
{
	if (true == _IsGround)
	{
		MoveDir.y = 0.0f;
	}
}

bool Troopa::LiftUp()
{
	while (true)
	{
		float4 NextPos = GetPos() ;

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


bool Troopa::CheckWall(float4 _Pivot)
{
	float4 CheckPos = GetPos();
	CheckPos += _Pivot;


	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}

bool Troopa::CheckAir()
{
	float4 CheckPos = GetPos();

	if (Magenta == Player::MainPlayer->ColImage->GetPixelColor(CheckPos + float4::Down, Black))
	{
		return true;
	}
	return false;
}

void Troopa::SetShellColOn()
{
	LeftShellCollision->On();
	RightShellCollision->On();
}

void Troopa::SetShellColOff()
{
	LeftShellCollision->Off();
	RightShellCollision->Off();
}

void Troopa::SetDirSwitch()
{
	if (0.0f > Dir.x)
	{
		Dir = float4::Right;
	}
	else if (0.0f < Dir.x)
	{
		Dir = float4::Left;
	}
}



void Troopa::DirCheck(const std::string_view& _AnimationName)
{				
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (0.0f > Dir.x)
	{
		DirString = "Left_";
	}
	else if (0.0f < Dir.x)
	{
		DirString = "Right_";
	}
}


void Troopa::SetOnPointSet(int _Point)
{
	PointSet.On();
	PointSet.SetValue(_Point);
}

void Troopa::SetTroopaColOff()
{
	HeadCollision->Off();
	LeftBodyCollision->Off();
	RightBodyCollision->Off();
	RightShellCollision->Off();
	LeftShellCollision->Off();
}


void Troopa::MonsterMove(float _DeltaTime)
{
	switch (StateValue)
	{
	case MonsterState::IDLE:
	{
		IdleUpdate(_DeltaTime);
		break;
	}
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
	case MonsterState::SHELL:
	{
		ShellUpdate(_DeltaTime);
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

void Troopa::IdleUpdate(float _DeltaTime)
{
	
	WaitTime -= _DeltaTime;
	DirCheck("TroopaShell");
	MoveDir = float4::Zero;

	if (true == LeftShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		SetEffectSound("kick.wav");
		Dir = float4::Right;

		StateValue = MonsterState::SHELL;
		return;
	}
	else if (true == RightShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		SetEffectSound("kick.wav");
		Dir = float4::Left;

		StateValue = MonsterState::SHELL;
		return;
	}
	else if (false == LeftShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		&& (false == RightShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })))
	{
		if (0.0f >= WaitTime)
		{
			DirCheck("TroopaIdle");
			HeadCollision->On();
			LeftBodyCollision->On();
			RightBodyCollision->On();
			SetShellColOff();

			WaitTime = 2.0f;
			TimerStart = false;
			count = 0;
			StateValue = MonsterState::MOVE;
			return;
		}
	}
}

void Troopa::MoveUpdate(float _DeltaTime)
{
	DirCheck("TroopaIdle");
	MoveDir = Dir * MoveSpeed * _DeltaTime;
	SetMove(MoveDir);

	if (true == CheckWall(PivotLPos))
	{
		Dir = float4::Right;
		DirCheck("TroopaIdle");
	}

	if (true == CheckWall(PivotRPos))
	{
		Dir = float4::Left;
		DirCheck("TroopaIdle");
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
	
		SetDirSwitch();
	}

	if (true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		SetDirSwitch();
	}

	DirCheck("TroopaIdle");
}


void Troopa::FallUpdate(float _DeltaTime)
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

void Troopa::ShellUpdate(float _DeltaTime)
{
	WaitTime -= _DeltaTime;

	DirCheck("TroopaShell");
	AccGravity(_DeltaTime);
	MoveSpeed = 500.0f;
	MoveDir = Dir * MoveSpeed * _DeltaTime;
	SetMove(MoveDir);

	if (true == CheckWall(PivotLPos))
	{
		SetEffectSound("bump.wav");
		Dir = float4::Right;
		DirCheck("TroopaShell");
	}

	if (true == CheckWall(PivotRPos))
	{
		SetEffectSound("bump.wav");
		Dir = float4::Left;
		DirCheck("TroopaShell");
	}


	if (0.0f >= WaitTime)
	{
		if ((true == RightShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			|| (true == LeftShellCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			)
		{
			if (false == Player::InvincibleMode)
			{
				if (Player::ModeValue == PlayerMode::SUPERMARIO || Player::ModeValue == PlayerMode::FIREMARIO)
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
	}



	SetMove(MoveDir * _DeltaTime);

	IsGround = LiftUp();
	InitGravity(IsGround);

	if (GetLevel()->GetCameraPos().x > GetPos().x)
	{
		Death();
	}
}

void Troopa::DeathUpdate(float _DeltaTime)
{

	AccGravity(_DeltaTime);
	SetMove(MoveDir * _DeltaTime);
	
	SetTroopaColOff();
	SetOnPointSet(Point);

	if (true == TimerStart)
	{
		WaitTime -= _DeltaTime;
		PointSet.SetMove(float4::Up * NumSpeed * _DeltaTime);
		if (0.0f >= WaitTime)
		{
			DeathMon->Death();
			TimerStart = false;
			WaitTime = 0.3f;

			return;
		}
	}
}


void Troopa::Render(float _DeltaTime)
{
	//HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();
	//ActorPos += PivotLPos;
	////ActorPos.x -= ImgHalfWidth;

	////<디버깅용_센터 보기위함>
	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);

	//float4 right = GetPos() - GetLevel()->GetCameraPos();
	//right += PivotRPos;

	////<디버깅용_NextPos 보기위함>
	//Rectangle(DoubleDC,
	//	right.ix() - 5,
	//	right.iy() - 5,
	//	right.ix() + 5,
	//	right.iy() + 5
	//);



}