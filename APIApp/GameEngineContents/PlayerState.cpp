#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnums.h"
#include "PlayLevel.h"
#include "EndingBack.h"
#include "Pipe.h"
#include "QuestionBlock.h"
#include "Effect.h"

std::string Player::GetStateName()
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		return "PlayerState::IDLE";
	case PlayerState::MOVE:
		return "PlayerState::MOVE";
	case PlayerState::BRAKE:
		return "PlayerState::BRAKE";
	case PlayerState::JUMP:
		return "PlayerState::JUMP";
	case PlayerState::CROUCH:
		return "PlayerState::CROUCH";
	case PlayerState::ATTACK:
		return "PlayerState::ATTACK";
	case PlayerState::GROW:
		return "PlayerState::GROW";
	case PlayerState::FALL:
		return "PlayerState::FALL";
	case PlayerState::DEATH:
		return "PlayerState::DEATH";
	case PlayerState::ENTERPIPE:
		return "PlayerState::ENTERPIPE";
	case PlayerState::ENTERLPIPE:
		return "PlayerState::ENTERLPIPE";
	case PlayerState::EXITPIPE:
		return "PlayerState::EXITPIPE";
	case PlayerState::FALG:
		return "PlayerState::FALG";
	case PlayerState::GOCASTLE:
		return "PlayerState::GOCASTLE";
	default:
		break;
	}
	return "";
}


//State 변경
void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::BRAKE:
		BrakeStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::CROUCH:
		CrouchStart();
		break;
	case PlayerState::ATTACK:
		AttackStart();
		break;
	case PlayerState::GROW:
		GrowStart();
		break;
	case PlayerState::FALL:
		FallStart();
		break;
	case PlayerState::DEATH:
		DeathStart();
		break;
	case PlayerState::ENTERPIPE:
		EnterPipeStart();
		break;
	case PlayerState::ENTERLPIPE:
		EnterLPipeStart();
		break;
	case PlayerState::EXITPIPE:
		ExitPipeStart();
		break;
	case PlayerState::FALG:
		FlagStart();
		break;
	case PlayerState::GOCASTLE:
		GoCastleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::BRAKE:
		BrakeEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
		break;
	case PlayerState::CROUCH:
		CrouchEnd();
		break;
	case PlayerState::ATTACK:
		AttackEnd();
		break;
	case PlayerState::GROW:
		GrowEnd();
		break;
	case PlayerState::FALL:
		FallEnd();
		break;
	case PlayerState::DEATH:
		DeathEnd();
		break;
	case PlayerState::ENTERPIPE:
		EnterPipeEnd();
		break;
	case PlayerState::ENTERLPIPE:
		EnterLPipeEnd();
		break;
	case PlayerState::EXITPIPE:
		ExitPipeEnd();
		break;
	case PlayerState::FALG:
		FlagEnd();
		break;
	case PlayerState::GOCASTLE:
		GoCastleEnd();
		break;
	default:
		break;
	}

}

void Player::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::BRAKE:
		BrakeUpdate(_Time);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
		break;
	case PlayerState::CROUCH:
		CrouchUpdate(_Time);
		break;
	case PlayerState::ATTACK:
		AttackUpdate(_Time);
		break;
	case PlayerState::GROW:
		GrowUpdate(_Time);
		break;
	case PlayerState::FALL:
		FallUpdate(_Time);
		break;
	case PlayerState::DEATH:
		DeathUpdate(_Time);
		break;
	case PlayerState::ENTERPIPE:
		EnterPipeUpdate(_Time);
		break;
	case PlayerState::ENTERLPIPE:
		EnterLPipeUpdate(_Time);
		break;
	case PlayerState::EXITPIPE:
		ExitPipeUpdate(_Time);
		break;
	case PlayerState::FALG:
		FlagUpdate(_Time);
		break;
	case PlayerState::GOCASTLE:
		GoCastleUpdate(_Time);
		break;
	default:
		break;
	}
}


void Player::IdleStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		DirCheck("GrowthIdle");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireIdle");
	}
	else
	{
		DirCheck("Idle");
	}
}
void Player::IdleUpdate(float _Time)
{
	if (true == IsShrink)
	{
		SetIsAlphaSwitch();
		ShrinkEffect(_Time);
	}

	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; 
	}

	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (ModeValue != PlayerMode::MARIO && GameEngineInput::IsPress("Crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (ModeValue == PlayerMode::FIREMARIO && GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATTACK);
		return;
	}

	if (false == GameEngineInput::IsAnyKey())		//move하면서 jump를 연속으로 하다가 idle상태로 오면
	{
		Friction(MoveDir, _Time);					//x값이 남아 계속 움직이는 문제 해결
	}



	if ((false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		AccGravity(_Time);

	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });
		//ChangeState(PlayerState::IDLE);
		//return;
	}

	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::IdleEnd() 
{
}



void Player::MoveStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		DirCheck("GrowthMove");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireMove");
	}
	else
	{
		DirCheck("Move");
	}
}
void Player::MoveUpdate(float _Time)
{
	if (true == IsShrink)
	{
		SetIsAlphaSwitch();
		ShrinkEffect(_Time);
	}

	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove")
		)
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (ModeValue != PlayerMode::MARIO && true == GameEngineInput::IsDown("Crouch"))
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (ModeValue == PlayerMode::FIREMARIO && GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATTACK);
		return;
	}

	//Brake State로 넘김------------------------------------
	if (
		(0 > MoveDir.x) &&									//왼쪽으로 가던 중에 오른쪽으로 감
		(true == GameEngineInput::IsPress("RightMove"))
		)
	{
		IsLeftBrake = true;
		ChangeState(PlayerState::BRAKE);
		return;
	}
	
	if (
		(0 < MoveDir.x) &&									//오른쪽으로 가던 중에 왼쪽으로 감
		(true == GameEngineInput::IsPress("LeftMove"))
		)
	{
		IsLeftBrake = false;
		ChangeState(PlayerState::BRAKE);
		return;
	}

	//Jump State로 넘김------------------------------------
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed * _Time;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed * _Time;
	}
	



	if (true == GameEngineInput::IsPress("LeftMove") && true == CheckWall(MoveDir * _Time, PivotLPos))
	{
		MoveDir.x = 0.0f;

		if (true == GameEngineInput::IsPress("RightMove"))				//왼쪽으로 가던 중에 오른쪽으로 감
		{
			if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
			{
				AnimationRender->ChangeAnimation("Right_GrowthMove");
			}
			else if (ModeValue == PlayerMode::FIREMARIO)											//Growth ver.Mario
			{
				AnimationRender->ChangeAnimation("Right_FireMove");
			}
			else
			{
				AnimationRender->ChangeAnimation("Right_Move");
			}
			return;
		}

	}
	else if (true == GameEngineInput::IsPress("RightMove") && true == CheckWall(MoveDir * _Time, PivotRPos))
	{
		MoveDir.x = 0.0f;

		if (true == GameEngineInput::IsPress("LeftMove"))				//오른쪽으로 가던 중에 왼쪽으로 감
		{
			ChangeState(PlayerState::MOVE);
			return;
		}
	}



	LimitSpeed(MoveDir);
	//AccGravity(_Time);
	
	//Stand on blocks
	if ((false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		if (true == CheckAir(MoveDir * _Time))
		{
			ChangeState(PlayerState::FALL);
			return;
		}

		AccGravity(_Time);
	}
	else
	{
		float4 pos = GetPos();

		//MoveDir.y = pos.y;
		SetPos({ GetPos().x, pos.y });
	}

	

	



	SetMove(MoveDir* _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
	
}
void Player::MoveEnd() 
{
}


void Player::BrakeStart()
{
	BrakePower = 400.0f;
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		if (true == IsLeftBrake)
		{
			AnimationRender->ChangeAnimation("Right_GrowthBrake");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_GrowthBrake");
		}
	}
	else if (ModeValue == PlayerMode::FIREMARIO)											//Growth ver.Mario
	{
		if (true == IsLeftBrake)
		{
			AnimationRender->ChangeAnimation("Right_FireBrake");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_FireBrake");
		}
	}
	else
	{
		if (true == IsLeftBrake)
		{
			AnimationRender->ChangeAnimation("Right_Brake");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_Brake");
		}
	}
}
void Player::BrakeUpdate(float _Time)
{
	if (true == IsShrink)
	{
		SetIsAlphaSwitch();
		ShrinkEffect(_Time);
	}

	LimitSpeed(MoveDir);
	
	if (ModeValue != PlayerMode::MARIO && true == GameEngineInput::IsDown("Crouch"))
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (0 < MoveDir.x)
	{
		MoveDir.x -= BrakePower * _Time;			//좌측 이동(BrakePower 이동할 때 속도를 감속)
	}
	else {
		MoveDir.x += BrakePower * _Time;			//우측 이동
	}


	if (true == CheckWall(MoveDir * _Time, PivotLPos))
	{
		MoveDir.x = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}
	else if (true == CheckWall(MoveDir * _Time, PivotRPos))
	{
		MoveDir.x = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}


	
	if (LeftSpeed >= abs(MoveDir.x))						//남은 속도가 5.0f이하이면 상태를 바꿈
	{
		if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
		{
			ChangeState(PlayerState::IDLE);			//아무것도 안 눌리면 IDLE
			return;
		}
		else if (true == GameEngineInput::IsDown("Jump"))
		{
			ChangeState(PlayerState::JUMP);
			return;
		}
		else
		{
			ChangeState(PlayerState::MOVE);			//계속 누르고 있는 상황 등에서는 Move
			return;
		}
	}

	//Stand on blocks
	if ((false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		if (true == CheckAir(MoveDir * _Time))
		{
			ChangeState(PlayerState::FALL);
			return;
		}

		AccGravity(_Time);
	}
	else
	{
		float4 pos = GetPos();

		//MoveDir.y = pos.y;
		SetPos({ GetPos().x, pos.y });
	}

	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::BrakeEnd()
{
}


void Player::JumpStart()
{
	MoveDir.y = SuperJumpPower;											//점프를 하는 순간 큰 힘으로 빠르게 위로 올라가야 함
	Gravity = 1250.0f;												//아래로 떨어뜨리는 힘

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
		SetEffectSound("jump_superMario.wav");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireJump");
		SetEffectSound("jump_superMario.wav");
	}
	else if(ModeValue == PlayerMode::MARIO)
	{
		MoveDir.y = JumpPower;											//점프를 하는 순간 큰 힘으로 빠르게 위로 올라가야 함
		DirCheck("Jump");
		SetEffectSound("jump.wav");
	}	
	

}
void Player::JumpUpdate(float _Time)
{
	if (true == IsShrink)
	{
		SetIsAlphaSwitch();
		ShrinkEffect(_Time);
	}

	//좌우 방향키가 눌러져 있다면 점프를 해당 방향에 맞게 뜀
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		if ((false == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			&& (false == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			)
		{
			MoveDir += float4::Left * MoveSpeed * _Time;	
		}
		else
		{
			//Block과 충돌했으면 못 가게 막음
			MoveDir.x = 0.0f;
		}
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{

		if ((false == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			&& (false == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			)
		{
			MoveDir += float4::Right * MoveSpeed * _Time;

		}
		else
		{
			//Block과 충돌했으면 못 가게 막음
			MoveDir.x = 0.0f;
		}

		
	}

	if ((true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		|| (true == SHeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect })))
	{
		MoveDir.y = 0.0f;
		SetMove(float4::Down);
	}
	
	if ((true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		|| (true == SHeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect })))
	{
		MoveDir.y = 0.0f;
		SetMove(float4::Down);
	}

	//Attack while Jumping
	{
		WaitTime -= _Time;

		if (ModeValue == PlayerMode::FIREMARIO && true == GameEngineInput::IsDown("Attack"))
		{
			WaitTime = 0.2f;
			SetEffectSound("fireball.wav");
			DirCheck("FireAttack");												//캐릭터 모션
			float4 FirePos = GetPos();
			Effect* Actor = GetLevel()->CreateActor<Effect>(MarioRenderOrder::PlayerAttack);

			if (RightStr == DirString)
			{
				Actor->SetPos({ FirePos.x + 36, FirePos.y - ImgHalfHeight });
			}
			else
			{
				Actor->SetPos({ FirePos.x - 36, FirePos.y - ImgHalfHeight });
			}
			Actor->SetEffectDir(DirString);
			Actor->DirCheck("Fire");											//투사체 모션


		}
		if (ModeValue == PlayerMode::FIREMARIO && 0 >= WaitTime)
		{
			DirCheck("FireJump");
		}
	}


	//땅에 닿으면 Idle
	if (true == IsGround && 0 <= MoveDir.y)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	LimitSpeed(MoveDir);

	//점프는 점 2개를 검사해서 좀 더 위쪽에 있는 점이 false이면 x값을 0이 안 되게 함
	if (true == CheckWall(MoveDir * _Time, PivotLPos) && true == CheckWall(MoveDir*_Time, PivotLPos2))
	{
		MoveDir.x = 0;

		if (true == IsGround && 0 <= MoveDir.y)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}
	}
	else if (true == CheckWall(MoveDir * _Time, PivotRPos) && true == CheckWall(MoveDir * _Time, PivotRPos2))
	{
		MoveDir.x = 0;

		if (true == IsGround && 0 <= MoveDir.y)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}
	}

	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	if ((false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		AccGravity(_Time);

	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });

		ChangeState(PlayerState::IDLE);
		return;
	}
	
	IsGround = LiftUp();

	InitGravity(IsGround);
}
void Player::JumpEnd()
{
}


void Player::CrouchStart()
{
	if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireCrouch");
	}
	else
	{
		DirCheck("Crouch");
	}
	
}
void Player::CrouchUpdate(float _Time)
{
	if (true == IsShrink)
	{
		SetIsAlphaSwitch();
		ShrinkEffect(_Time);
	}

	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove") &&
		false == GameEngineInput::IsPress("Crouch")
		)
	{
		//Friction(MoveDir, _Time);
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	LimitSpeed(MoveDir);


	if ((false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		AccGravity(_Time);
	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });
		//ChangeState(PlayerState::IDLE);
		//return;
	}



	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::CrouchEnd()
{
}


void Player::AttackStart()
{
	WaitTime = 0.2f;
	SetEffectSound("fireball.wav");
	DirCheck("FireAttack");												//캐릭터 모션
	float4 FirePos = GetPos();
	Effect* Actor = GetLevel()->CreateActor<Effect>(MarioRenderOrder::PlayerAttack);

	if (RightStr == DirString)
	{
		Actor->SetPos({ FirePos.x + 36, FirePos.y - ImgHalfHeight });
	}
	else
	{
		Actor->SetPos({ FirePos.x - 36, FirePos.y - ImgHalfHeight });
	}

	Actor->SetEffectDir(DirString);
	Actor->DirCheck("Fire");
}
void Player::AttackUpdate(float _Time)
{
	WaitTime -= _Time;

	if (0 >= WaitTime)
	{
		if (true != GameEngineInput::IsAnyKey())
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		if (true == GameEngineInput::IsPress("RightMove") || true == GameEngineInput::IsPress("LeftMove"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		if (true == GameEngineInput::IsPress("Crouch"))
		{
			ChangeState(PlayerState::CROUCH);
			return;
		}

		if (true == GameEngineInput::IsPress("Jump"))
		{
			ChangeState(PlayerState::JUMP);
			return;
		}
	}

}
void Player::AttackEnd()
{
}

void Player::GrowStart()
{
	if (ModeValue == PlayerMode::MARIO)
	{
		ChangeMode(PlayerMode::SUPERMARIO);
		DirCheck("Bigger");
	}
	else
	{
		IsChanged = false;
	}

	SetEffectSound("growup.wav");
}
void Player::GrowUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		if (false == GameEngineInput::IsAnyKey())
		{
			Player::MainPlayer->ChangeState(PlayerState::IDLE);
			return;
		}

		if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
		{
			Player::MainPlayer->ChangeState(PlayerState::MOVE);
			return;
		}

		if (GameEngineInput::IsDown("Jump"))
		{
			Player::MainPlayer->ChangeState(PlayerState::JUMP);
			return;
		}

		if (GameEngineInput::IsPress("Crouch"))
		{
			Player::MainPlayer->ChangeState(PlayerState::CROUCH);
			return;
		}
	}

	
}
void Player::GrowEnd()
{
}

//(떨어지면 Jump모션을 취하며 Y값은 계속 증가)
void Player::FallStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireJump");
	}
	else
	{
		DirCheck("Jump");
	}
}
void Player::FallUpdate(float _Time)
{
	/*if (true == IsShrink)
	{
		ShrinkEffect(_Time);
	}*/

	LimitSpeed(MoveDir);


	

	if ((false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::QBlock), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		&& (false == BottomCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Brick), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		)
	{
		AccGravity(_Time);

	}
	else
	{
		float4 pos = GetPos();

		MoveDir.y = 0.0f;
		SetPos({ GetPos().x, pos.y });

		ChangeState(PlayerState::IDLE);
		return;
	}

	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);

	//땅에 닿으면 Idle
	if (true == IsGround)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::FallEnd()
{
}


void Player::DeathStart()
{
	WaitTime = 3.0f;
	MoveDir.y = -300.0f;
	Gravity = 1000.0f;


	SetPlayerColOff();

	PlayLevel::MainPlayLevel->SetBGMPlayer("Miss.mp3");
	DirCheck("Death");
}	
void Player::DeathUpdate(float _Time)
{
	SetMove(MoveDir * _Time);

	MoveDir.x = 0.0f;

	AccGravity(_Time);
	SetMove(MoveDir * _Time);
	
	WaitTime -= _Time;


	if (0 >= WaitTime)
	{
		AnimationRender->Off();
		EndingBack::Ending->SetEndingScene(EndingScene::GameOver);
		GameEngineCore::GetInst()->ChangeLevel("EndingLevel");
	}


}
void Player::DeathEnd()
{
}

void Player::EnterPipeStart()
{
	PlayLevel::MainPlayLevel->SetBGMPlayer("pipe.wav", 1);
	WaitTime = 0.8f;

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthIdle");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireIdle");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Idle");
	}
}
void Player::EnterPipeUpdate(float _Time)
{
   	WaitTime -= _Time;
	SetMove(float4::Down* PipeEnterSpeed *_Time);
	

	if (0 >= WaitTime)
	{
		IsUnderGround = true;
		PlayLevel::MainPlayLevel->SetBGMPlayer("Underground.mp3", MaxLoop);

		MoveDir.x = 0.0f;
		SetPos({ UnderGroundStart });
		GetLevel()->SetCameraPos(UnderGroundCameraPos);
		
		ChangeState(PlayerState::FALL);
		return;
	}
}
void Player::EnterPipeEnd()
{
}


void Player::EnterLPipeStart()
{
	PlayLevel::MainPlayLevel->SetBGMPlayer("pipe.wav", 1);
	WaitTime = 0.8f;

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthIdle");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireIdle");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Idle");
	}



}
void Player::EnterLPipeUpdate(float _Time)
{
	WaitTime -= _Time;
	SetMove(float4::Right * PipeEnterSpeed * _Time);


	if (0 >= WaitTime)
	{
		IsUnderGround = false;
		PlayLevel::MainPlayLevel->SetBGMPlayer("RunningAbout.mp3", MaxLoop);

		MoveDir.x = 0.0f;
		SetPos({ UnderGroundEnd });


		ChangeState(PlayerState::EXITPIPE);
		return;
	}
}
void Player::EnterLPipeEnd() 
{
}

void Player::ExitPipeStart()
{
	PlayLevel::MainPlayLevel->SetBGMPlayer("pipe.wav", 1);
	WaitTime = 0.9f;

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthIdle");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireIdle");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Idle");
	}

	SetPos({ UnderGroundEnd });
	GetLevel()->SetCameraPos({ GetPos().x - 100, 0.0f });
}
void Player::ExitPipeUpdate(float _Time)
{
	WaitTime -= _Time;
	SetMove(float4::Up * PipeEnterSpeed * _Time);


	if (0 >= WaitTime)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::ExitPipeEnd()
{
}


void Player::FlagStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthHang");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireHang");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Hang");
	}
	MoveDir.x = 0.0f;
	WaitTime = 1.0f;

	TimerStop = true;

	PlayLevel::MainPlayLevel->SetBGMPlayer("flagpole.wav");
}
void Player::FlagUpdate(float _Time)
{
	MoveDir = float4::Down * FlagDownSpeed;
	SetMove(MoveDir * _Time );

	if (true == FlagDownEnd)
	{
		WaitTime -= _Time;
		if (ModeValue == PlayerMode::SUPERMARIO)
		{
			AnimationRender->ChangeAnimation("Left_GrowthHang");
		}
		else if (ModeValue == PlayerMode::FIREMARIO)
		{
			AnimationRender->ChangeAnimation("Left_FireHang");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_Hang");
		}
		SetPos({ GetPos().x + 48, GetPos().y });
		FlagDownEnd = false;

		if (0.0f >= WaitTime);
		{
			ChangeState(PlayerState::GOCASTLE);
			return;
		
		}

	}


	if (true == IsGround)
	{
		FlagDownEnd = true;
	}


	IsGround = LiftUp();
	InitGravity(IsGround);


}
void Player::FlagEnd() 
{
}


void Player::GoCastleStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthMove");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireMove");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Move");
	}
	MoveSpeed = 150.0f;
	PlayLevel::MainPlayLevel->SetBGMPlayer("LevelComplete.mp3");

	WaitTime = 9.0f;
}
void Player::GoCastleUpdate(float _Time)
{
	WaitTime -= _Time;

	if (false == IsMoveStop)
	{
		SetMove(float4::Right * MoveSpeed * _Time);
	}

	if (RightBodyCollision != 0)
	{
		if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Door), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AnimationRender->Off();
			IsMoveStop = true;

			int Timer = static_cast<int>(PlayTimer);
			if (0 != Timer)
			{
				--PlayTimer;
				++TotalScore;

				EffectPlayer.Stop();
				SetEffectSound("coin.wav");
			}
			else
			{
				if (0 >= WaitTime)
				{
					EffectPlayer.Stop();
					IsMoveStop = false;
					++Round;
					NumOfCoin = 0;
					GameEngineCore::GetInst()->ChangeLevel("OpeningLevel");
				}

			}
		}
	}

	AccGravity(_Time);
	SetMove(MoveDir * _Time);


	IsGround = LiftUp();
	InitGravity(IsGround);


}
void Player::GoCastleEnd()
{
}