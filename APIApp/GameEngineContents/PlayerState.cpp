#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"




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
	case PlayerState::FALL:
		FallStart();
		break;
	case PlayerState::DEATH:
		DeathStart();
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
	case PlayerState::FALL:
		FallEnd();
		break;
	case PlayerState::DEATH:
		DeathEnd();
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
	case PlayerState::FALL:
		FallUpdate(_Time);
		break;
	case PlayerState::DEATH:
		DeathUpdate(_Time);
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

	if (false == GameEngineInput::IsAnyKey())		//move하면서 jump를 연속으로 하다가 idle상태로 오면
	{
		Friction(MoveDir, _Time);					//x값이 남아 계속 움직이는 문제 해결
	}

	AccGravity(_Time);
	ActorMove(_Time);

	IsGround = LiftUp();
    InitGravity(IsGround);
	
}
void Player::IdleEnd() {

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

	//Brake State로 넘김------------------------------------
	if (
		(0 > MoveDir.x) &&									//왼쪽으로 가던 중에 오른쪽으로 감
		(true == GameEngineInput::IsDown("RightMove"))
		)
	{
		IsLeftBrake = true;
		ChangeState(PlayerState::BRAKE);
		return;
	}
	
	if (
		(0 < MoveDir.x) &&									//오른쪽으로 가던 중에 왼쪽으로 감
		(true == GameEngineInput::IsDown("LeftMove")) 
		)
	{
		IsLeftBrake = false;
		ChangeState(PlayerState::BRAKE);
		return;
	}

 
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
	

	LimitSpeed(MoveDir);
	AccGravity(_Time);


	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);



	IsGround = LiftUp();
	InitGravity(IsGround);

	
}
void Player::MoveEnd() 
{

}


void Player::BrakeStart()
{
	BrakePower = 200.0f;
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
	LimitSpeed(MoveDir);
	AccGravity(_Time);

	if (ModeValue != PlayerMode::MARIO && true == GameEngineInput::IsDown("Crouch"))
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::CROUCH);
		return;
	}

	//Brake
	if (true == IsLeftBrake)									//왼쪽으로 가던 중에 오른쪽으로 이동하는 경우
	{
		if (
			0 <= MoveDir.x 
			&& false == GameEngineInput::IsPress("LeftMove")
			&& false == GameEngineInput::IsPress("RightMove")
			)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		if (0 <= MoveDir.x && true == GameEngineInput::IsPress("RightMove"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

			

		if (0 >= MoveDir.x && false == GameEngineInput::IsPress("RightMove") && true == GameEngineInput::IsPress("LeftMove"))
		{
			int a = 0;

		}


		MoveDir += float4::Left * _Time;
		MoveDir += float4::Right * BrakePower * _Time;

		SetMove(MoveDir * _Time);
		Camera(MoveDir * _Time);


	}
	else if (false == IsLeftBrake)								//오른쪽으로 가던 중에 왼쪽으로 이동하는 경우
	{
		if (
			0 >= MoveDir.x
			&& false == GameEngineInput::IsPress("LeftMove")
			&& false == GameEngineInput::IsPress("RightMove")
			)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		if (0 >= MoveDir.x && true == GameEngineInput::IsPress("LeftMove"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}



		//오른쪽으로 가다가 왼쪽 이동키를 누르면 오른쪽으로 미끄러짐(관성)
		//오른쪽으로 미끄러지고 있는데, 왼쪽 키에서 손을 떼고  다시 오른쪽키를 누름
		//미끄러지는 모션을 유지한채로 왼쪽으로 이동
		if (0 <= MoveDir.x && true == GameEngineInput::IsPress("RightMove") ) //&& false == GameEngineInput::IsPress("LeftMove")
		{
			int a = 0;


		}

	
		MoveDir += float4::Right * _Time;
		MoveDir += float4::Left * BrakePower * _Time;

		SetMove(MoveDir * _Time);
		Camera(MoveDir * _Time);
	}


	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}



	//가다가 땅이 아니라면 Fall로 changestate
	


	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::BrakeEnd()
{
}


void Player::JumpStart()
{
	MoveDir.y = -700.0f;											//점프를 하는 순간 큰 힘으로 빠르게 위로 올라가야 함
	Gravity = 1000.0f;												//아래로 떨어뜨리는 힘

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
void Player::JumpUpdate(float _Time)
{
	//좌우 방향키가 눌러져 있다면 점프를 해당 방향에 맞게 뜀
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed * _Time;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed * _Time;
	}


	//땅에 닿으면 Idle
	if (true == IsGround && 0 <= MoveDir.y)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}


	LimitSpeed(MoveDir);

	SetMove(MoveDir*_Time);
	AccGravity(_Time);

	Camera(MoveDir * _Time);

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

	SetMove(MoveDir * _Time);
	AccGravity(_Time);

	Camera(MoveDir * _Time);

	IsGround = LiftUp();

	InitGravity(IsGround);
}
void Player::CrouchEnd()
{

}


void Player::AttackStart()
{

}
void Player::AttackUpdate(float _Time)
{

}
void Player::AttackEnd()
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
	//땅에 닿으면 Idle
	if (true == IsGround)
	{
		ChangeState(PlayerState::IDLE);
		IsGround = LiftUp();
		InitGravity(IsGround);

		return;
	}



	LimitSpeed(MoveDir);
	AccGravity(_Time);
	SetMove(MoveDir * _Time);

	Camera(MoveDir * _Time);

}
void Player::FallEnd()
{

}



void Player::DeathStart()
{
	MoveDir.y = -300.0f;
	Gravity = 1000.0f;

	DirCheck("Death");
	
}
void Player::DeathUpdate(float _Time)
{
	
}
void Player::DeathEnd()
{

}


